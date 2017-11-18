#include <stdafx.h>

#include "cube/rubik.h"
#include "cube/solver.h"
#include "cv/color.h"
#include "cv/cube_classify.h"
#include "motor_op.h"

#include "stb_image.h"

/* full cube rotations to perform while scanning */
rubik_side_t    SCAN_CUBE_OP_MAT[]           = {R_LEFT, R_LEFT, R_LEFT, R_FRONT, R_UP, R_NOSIDE};
/* face rotations to orient final cube */
rubik_dir_t     SCAN_IMAGE_OP_MAT[]          = {R_NODIR, R_CW, R_DOUBLE_CW, R_CCW, R_CCW, R_CCW};
/* map scan order to rubiks cube face order (ie. URDLBF -> URFDLB) */
int             SCAN_ORDER_TO_FACE_ORDER[]   = {0, 1, 3, 4, 5, 2};
/* (x1, y1) (x2, y2) coordinates region containing cube face */
const int       SCAN_BOUNDS[]                = {1064, 546, 3061, 2549};

int fake_idx = 0;
uint8_t* fake_cube_classify_read_webcam(int *width, int *height, int *bpp){
    char buf[256];
    sprintf(buf, "../experimental/0%d.jpg", fake_idx++);
    return stbi_load(buf, width, height, bpp, 3);
}

rubik_cube_t scan_cube(){
    uint8_t *image;
    rgb_t color_mat[6][3][3];
    int width, height, bpp;
    // image every face, and create rgb matrices of each face based on average color
    for(int i = 0; i < 6; i++){
        image = fake_cube_classify_read_webcam(&width, &height, &bpp);
        LOG("read face %d", i);
        cube_classify_face_image_argb(image, bpp, width, height, 
            SCAN_BOUNDS[0], SCAN_BOUNDS[1], SCAN_BOUNDS[2], SCAN_BOUNDS[3], 0.2f,
            color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
            free(image);
        motor_op_rotate_cube(SCAN_CUBE_OP_MAT[i]);
    }    
    LOG("classifying...");
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                printf("(%f,%f,%f) ", color_mat[f][y][x].r, color_mat[f][y][x].g, color_mat[f][y][x].b);
            }
            printf("\n");
        }
        printf("\n");
    }
    rubik_cube_t cube = cube_classify_from_colors(color_mat);
    LOG("cube built!");

    // since the faces are not necessarily imaged in the correct orientation, rotate them accordingly
    for(int i = 0; i < 6; i++){
        rubik_face_rotate(cube.faces[i], SCAN_IMAGE_OP_MAT[SCAN_ORDER_TO_FACE_ORDER[i]]);
    }
    return cube;
}

int main(void){
    srand(time(NULL));

    rubik_cube_t cube = scan_cube();
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                printf("%d ", cube.faces[f].colors[y][x]);
            }
            printf("\n");
        }
        printf("\n");
    }
    rubik_solution_t solution = rubik_solve(cube);
    printf("%s\n", solution.str);
    assert(solution.error_code == 0);
    

    // TODO: transform sequence into a full rotation sequence w/o up and down
    
    for(int i = 0; i < solution.seq.length; i++){
        motor_op_rotate_face(
            solution.seq.operations[i].side, 
            solution.seq.operations[i].direction);
        motor_op_rotate_cube(solution.seq.operations[i].rotation);
    }
    rubik_destroy_solution(&solution);
    return 0;
}