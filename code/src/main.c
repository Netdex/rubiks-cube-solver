#include <stdafx.h>

#include "cube/rubik.h"
#include "cube/solver.h"
#include "cv/color.h"
#include "cv/cube_classify.h"
#include "motor_op.h"
#include "motor.h"

#include "stb_image.h"

/* full cube rotations to perform while scanning */
rubik_side_t    SCAN_CUBE_OP_MAT[]           = {R_LEFT, R_LEFT, R_LEFT, R_FRONT, R_UP, R_NOSIDE};
/* face rotations to orient final cube */
rubik_dir_t     SCAN_IMAGE_OP_MAT[]          = {R_NODIR, R_CW, R_CCW, R_CCW, R_DOUBLE_CW, R_CCW};
/* map scan order to rubiks cube face order (ie. URDLBF -> URFDLB) */
int             SCAN_ORDER_TO_FACE_ORDER[]   = {0, 1, 3, 4, 5, 2};
/* (x1, y1) (x2, y2) coordinates region containing cube face */
const int       SCAN_BOUNDS[]                = {1064, 546, 3061, 2549};

/* reads images from file for debugging */
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
        // remove "fake" for real case
        image = fake_cube_classify_read_webcam(&width, &height, &bpp); 
        LOG("read face %d", i);
        cube_classify_face_image_argb(image, bpp, width, height, 
            SCAN_BOUNDS[0], SCAN_BOUNDS[1], SCAN_BOUNDS[2], SCAN_BOUNDS[3], 0.2f,
            color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
            free(image);
        motor_op_rotate_cube(SCAN_CUBE_OP_MAT[i]);
    }    
    printf("\ncube color output:\n");
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                printf("(%.2f,%.2f,%.2f) ", 
                    color_mat[f][y][x].r, color_mat[f][y][x].g, color_mat[f][y][x].b);
            }
            printf("\n");
        }
        printf("\n");
    }
    LOG("classifying...");
    rubik_cube_t cube = cube_classify_from_colors(color_mat);
    LOG("cube built!");

    // since the faces are not necessarily imaged in the correct orientation, 
    // rotate them accordingly
    for(int i = 0; i < 6; i++){
        cube.faces[i] = rubik_face_rotate(cube.faces[i], 
            SCAN_IMAGE_OP_MAT[SCAN_ORDER_TO_FACE_ORDER[i]]);
    }
    return cube;
}

int main(void) {
    printf("Starting up...\n");
    motor motors[] = {
        {43,44,45,46},     // F
        {7,8,9,10},        // B
        {39,40,41,42},     // L
        {15,16,17,18},     // R
        {19,20,21,22},     // L/R retract/extend
        {35,36,37,38},     // F/B retract/extend
    };

    printf("Initializing motors...\n");
    for (int i = 0; i < 6; i++) {
        motor_init(motors[i]);
    }
    printf("Motors initialized\n");
    q_turn(motors[0], DIR_CW);

    return 0;
}

/*int main(void){
    srand(time(NULL));

    rubik_cube_t cube = scan_cube();
    printf("\ncube matrix output:\n");
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
    LOG("generated sequence: %s", solution.str);
    assert(solution.error_code == 0);
    
    LOG("optimizing sequence");
    // TODO: transform sequence into a full rotation sequence w/o up and down
    // The solution rubik_cube_remove_up_down needs to be fixed!
    rubik_sequence_t trunc = rubik_cube_remove_up_down(&solution.seq);
    char *str = rubik_sequence_to_string(&trunc);
    LOG("optimized sequence: %s\n", str);
    free(str);
    
    LOG("running sequence");
    for(int i = 0; i < trunc.length; i++){
        motor_op_rotate_cube(trunc.operations[i].rotation);
        if(trunc.operations[i].rotation != R_NOSIDE){
            printf("%c", 
                RUBIK_MAP_ROT_CHAR[trunc.operations[i].rotation]);
        }
        motor_op_rotate_face(
            trunc.operations[i].side, 
            trunc.operations[i].direction);
        if(trunc.operations[i].side != R_NOSIDE 
            && trunc.operations[i].direction != R_NODIR){
            printf("%c%c", 
                RUBIK_MAP_FACE_CHAR[trunc.operations[i].side], 
                RUBIK_MAP_DIR_CHAR[trunc.operations[i].direction]);
        }
        printf(" ");
    }
    printf("\n");
    LOG("done!");
    
    rubik_destroy_solution(&solution);
    rubik_destroy_sequence(&trunc);
    return 0;
}*/
