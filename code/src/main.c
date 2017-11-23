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
rubik_dir_t     SCAN_IMAGE_OP_MAT[]          = {R_NODIR, R_CW, R_NODIR, R_NODIR, R_CCW, R_DOUBLE_CW};
/* map scan order to rubiks cube face order (ie. FBLRUD -> URFDLB) */
int             SCAN_ORDER_TO_FACE_ORDER[]   = {2, 5, 4, 1, 0, 3};
/* (x1, y1) (x2, y2) coordinates region containing cube face */
//const int       SCAN_BOUNDS[]                = {1064, 546, 3061, 2549};

/* reads images from file for debugging */
int fake_idx = 0;
uint8_t* fake_cube_classify_read_webcam(int *width, int *height, int *bpp){
    char buf[256];
    sprintf(buf, "../experimental/0%d.jpg", fake_idx++);
    return stbi_load(buf, width, height, bpp, 3);
}

rubik_cube_t scan_cube(){
#ifndef NO_GPIO
    log_info("performing cube scan...");
    uint8_t *image;
    rgb_t color_mat[6][3][3];
    int width, height, bpp, i = 0;
    // image every face, and create rgb matrices of each face based on average color
    
    // Image front face
    motor_op_rotate_cube(R_BACK);
    image = cube_classify_read_webcam(&width, &height, &bpp); 
    log_info("read face %d", i);
    cube_classify_face_image_argb(image, bpp, width, height, 
        color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
    free(image);
    i++;

    // Image back face
    motor_op_rotate_cube(R_FRONT);
    motor_op_rotate_cube(R_FRONT);
    image = cube_classify_read_webcam(&width, &height, &bpp); 
    log_info("read face %d", i);
    cube_classify_face_image_argb(image, bpp, width, height, 
        color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
    free(image);
    i++;
    
    // Image left face
    motor_op_rotate_cube(R_BACK);
    motor_op_rotate_cube(R_RIGHT);
    image = cube_classify_read_webcam(&width, &height, &bpp); 
    log_info("read face %d", i);
    cube_classify_face_image_argb(image, bpp, width, height, 
        color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
    free(image);
    i++;
    
    // Image right face
    motor_op_rotate_cube(R_LEFT);
    motor_op_rotate_cube(R_LEFT);
    image = cube_classify_read_webcam(&width, &height, &bpp); 
    log_info("read face %d", i);
    cube_classify_face_image_argb(image, bpp, width, height, 
        color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
    free(image);
    i++;

    // Image top face
    motor_op_rotate_cube(R_RIGHT);
    motor_op_rots(MOTOR_L, DIR_CW, MOTOR_R, DIR_CCW, 0);
    motor_op_arm_move(ARM_LR, ARM_RETRACT);
    motor_op_arm_move(ARM_FB, ARM_EXTEND);
    image = cube_classify_read_webcam(&width, &height, &bpp); 
    log_info("read face %d", i);
    cube_classify_face_image_argb(image, bpp, width, height, 
        color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
    free(image);
    i++;

    // Image bottom face
    motor_op_rotate_cube(R_FRONT);
    motor_op_rotate_cube(R_FRONT);
    image = cube_classify_read_webcam(&width, &height, &bpp); 
    log_info("read face %d", i);
    cube_classify_face_image_argb(image, bpp, width, height, 
        color_mat[SCAN_ORDER_TO_FACE_ORDER[i]]);
    free(image);
    motor_op_rotate_cube(R_BACK);

    log_trace("cube color output:");
    
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            char dbuf[1024] = {0};
            for(int x = 0; x < 3; x++){
                char tbuf[256] = {0};
                sprintf(tbuf, "(%.2f,%.2f,%.2f) ", color_mat[f][y][x].r, color_mat[f][y][x].g, color_mat[f][y][x].b);
                strcat(dbuf, tbuf);
            }
            log_trace("%s", dbuf);
        }
        log_trace("");
    }
    log_info("classifying...");
    rubik_cube_t cube = cube_classify_from_colors(color_mat);
    log_info("cube built!");

    // since the faces are not necessarily imaged in the correct orientation, 
    // rotate them accordingly
    for(int i = 0; i < 6; i++){
        cube.faces[i] = rubik_face_rotate(cube.faces[i], SCAN_IMAGE_OP_MAT[i]);
    }
    return cube;
#else
    // for debugging
    char c[6][3][3] = {0};
    printf("Enter cube: \n");
    scanf("\n");
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++)
                scanf("%c", &c[f][y][x]);
        }
    }
    rubik_cube_t cube = rubik_make_cube_from_char(c);
    return cube;
#endif
}

int main(void){
    log_set_level(LOG_TRACE);

    motor_op_init();

    motor_op_arm_move(ARM_LR, ARM_RETRACT);
    motor_op_arm_move(ARM_FB, ARM_RETRACT);

    do {
        int c;
        do {
            printf(
                "\n\nrbs1 - rubik's cube solver\n"
                "1. solve cube to solved state\n"
                "2. solve cube to defined state\n");
            scanf("%d", &c);
        } while(c < 1 || c > 2);

        rubik_solution_t solution;
        rubik_cube_t cube = scan_cube();
        log_trace("cube matrix output:");
        for(int f = 0; f < 6; f++){
            for(int y = 0; y < 3; y++){
                char dbuf[1024] = {0};
                for(int x = 0; x < 3; x++){
                    char tbuf[256] = {0};
                    sprintf(tbuf, "%d ", cube.faces[f].colors[y][x]);
                    strcat(dbuf, tbuf);
                }
                log_trace("%s", dbuf);
            }
            log_trace("");
        }

        switch(c){
            case 1:
            {
                solution = rubik_solve(cube);
            }
            break;
            case 2:
            {
                /*
                    EXAMPLE:
                    GOBWWWGOBYGYYOYYBYOBROBROBRBRGYYYBRGWBWWRWWGWOGROGROGR
                    YWYWYWYWYOROROROROBGBGBGBGBWYWYWYWYWRORORORORGBGBGBGBG
                */
                char c[6][3][3];
                printf("enter target state: \n");
                scanf("\n");
                for(int f = 0; f < 6; f++){
                    for(int y = 0; y < 3; y++){
                        for(int x = 0; x < 3; x++)
                            scanf("%c", &c[f][y][x]);
                    }
                }
                rubik_cube_t target = rubik_make_cube_from_char(c);
                solution = rubik_solve_pattern(cube, target);
            }
            break;
        }
        
        log_info("generated sequence: %s", solution.str);
        if(solution.error_code != 0){
            motor_op_arm_move(ARM_LR, ARM_EXTEND);
            motor_op_arm_move(ARM_FB, ARM_EXTEND);
            log_error("unexpected solution code, invalid cube state!");
            continue;
        }
        
        rubik_sequence_rotate(&solution.seq, 0, solution.seq.length, R_FRONT);

        log_info("rotated sequence: %s", solution.str);

        log_info("optimizing sequence...");
        // TODO: transform sequence into a full rotation sequence w/o up and down
        // The solution rubik_cube_remove_up_down needs to be fixed!
        rubik_sequence_t trunc = rubik_cube_remove_up_down(&solution.seq);
        char *str = rubik_sequence_to_string(&trunc);
        log_info("optimized sequence: %s", str);
        free(str);
        
        log_info("running sequence");
        for(int i = 0; i < trunc.length; i++){
            if(trunc.operations[i].rotation != R_NOSIDE){
                log_debug("execute rotate %c", 
                    RUBIK_MAP_ROT_CHAR[trunc.operations[i].rotation]);
                motor_op_rotate_cube(trunc.operations[i].rotation);
            }

            if(trunc.operations[i].side != R_NOSIDE 
                && trunc.operations[i].direction != R_NODIR){
                log_debug("execute face %c%c", 
                    RUBIK_MAP_FACE_CHAR[trunc.operations[i].side], 
                    RUBIK_MAP_DIR_CHAR[trunc.operations[i].direction]);

                motor_op_rotate_face(
                    FACE_TO_MOTOR[trunc.operations[i].side], 
                    trunc.operations[i].direction);
            }
        }
        log_info("done!");
        rubik_destroy_solution(&solution);
        rubik_destroy_sequence(&trunc);
    } while(1);
    
    motor_op_reset();
    return 0;
}
