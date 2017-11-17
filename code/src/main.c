#include <stdafx.h>

#include "cube/rubik.h"
#include "cube/solver.h"
#include "cv/color.h"
#include "cv/cube_classify.h"
#include "motor_op.h"

/* full cube rotations to perform while scanning */
rubik_side_t    SCAN_CUBE_OP_MAT[]           = {R_LEFT, R_LEFT, R_LEFT, R_FRONT, R_UP, R_NOSIDE};
/* face rotations to orient final cube */
rubik_dir_t     SCAN_IMAGE_OP_MAT[]          = {R_NODIR, R_CW, R_DOUBLE_CW, R_CCW, R_CCW, R_CCW};
/* map scan order to rubiks cube face order (ie. URDLBF -> URFDLB) */
int             SCAN_ORDER_TO_FACE_ORDER[]   = {0, 1, 3, 4, 5, 2};
/* (x1, y1) (x2, y2) coordinates region containing cube face */
const int       SCAN_BOUNDS[]                = {-1, -1, -1, -1};

rubik_cube_t scan_cube(){
    uint8_t *image;
    rgb_t color_mat[6][3][3];
    int width, height, bpp;
    // image every face, and create rgb matrices of each face based on average color
    for(int i = 0; i < 6; i++){
        image = cube_classify_read_webcam(&width, &height, &bpp);
        cube_classify_face_image_argb(image, bpp, width, height, 
            SCAN_BOUNDS[0], SCAN_BOUNDS[1], SCAN_BOUNDS[2], SCAN_BOUNDS[3], 
            color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
        motor_op_rotate_cube(SCAN_CUBE_OP_MAT[i]);
    }    
    rubik_cube_t cube = cube_classify_from_colors(color_mat);
    
    // since the faces are not necessarily imaged in the correct orientation, rotate them accordingly
    for(int i = 0; i < 6; i++){
        rubik_face_rotate(cube.faces[i], SCAN_IMAGE_OP_MAT[SCAN_ORDER_TO_FACE_ORDER[i]]);
    }
    return cube;
}

int main(void){
    rubik_cube_t cube = scan_cube();
    rubik_solution_t solution = rubik_solve(cube);
    
    // transform sequence into a full rotation sequence w/o up and down
    
    assert(solution.error_code == 0);
    printf("%s\n", solution.str);
    for(int i = 0; i < solution.seq.length; i++){
        motor_op_rotate_face(
            solution.seq.operations[i].side, 
            solution.seq.operations[i].direction);
        motor_op_rotate_cube(solution.seq.operations[i].rotation);
    }
    return 0;
}