#include "stdafx.h"
#include "motor_op.h"
#include "motor.h"

/* map rubik_face_t to appropriate motor */
int FACE_TO_MOTOR[] = {-1, 3, 0, -1, 2, 1};
/* index i, is motor steps to achieve operation i */
const int ARM_OP_STEPS[] = {0, 1900, 2950};
/* grabbers A[i] must be vertical when doing a rotation on face i */
int MOTOR_REQ_VERT[4][2] = {
    {MOTOR_L, MOTOR_R},     // F
    {MOTOR_R, MOTOR_L},     // B
    {MOTOR_F, MOTOR_B},     // L
    {MOTOR_B, MOTOR_F}      // R
};
/* grabbers A[i] must be vertical when doing a rotation on face i */
int MOTOR_REQ_VERT_INV[4][2] = {
    {MOTOR_F, MOTOR_B},     // F
    {MOTOR_B, MOTOR_F},     // B
    {MOTOR_L, MOTOR_R},     // L
    {MOTOR_R, MOTOR_L}      // R
};
/* given an arm motor, produces the motors which are on that axis */
int ARM_TO_MOTOR[6][2] = {
    {-1, -1},
    {-1, -1},
    {-1, -1},
    {-1, -1},
    {MOTOR_F, MOTOR_B}, // FB
    {MOTOR_L, MOTOR_R}  // LR
};
/* parallel arm to rotation on motor i */
int ROT_ARM[4] = { MOTOR_FB, MOTOR_FB, MOTOR_LR, MOTOR_LR};
/* perpendicular arm to rotation on motor i */
int PERP_ARM[4] = { MOTOR_LR, MOTOR_LR, MOTOR_FB, MOTOR_FB };

/* GPIO pinout for motors */
motor motors[] = {
    {9, 11, 12, 13, 14}, // F
    {8, 37, 38, 39, 40}, // B
    {8, 33, 34, 35, 36}, // L
    {8, 11, 12, 13, 14}, // R
    {8, 7, 8, 9, 10},    // F/B retract/extend
    {8, 15, 16, 17, 18}, // L/R retract/extend
};

/* motor position state for optimizing moves */


union motor_op_state {
    struct {
        // (vertical = 0, horizontal = 1)
        int f;      // position of front grabber
        int b;      // position of back grabber
        int l;      // position of left grabber
        int r;      // position of right grabber
        // (retracted = 0, partial = 1, extended = 2)
        int fb;     // position of f/b arm
        int lr;     // position of l/r arm
    };
    int pos[6];    // grabber positions
} state = {{G_VERT, G_VERT, G_VERT, G_VERT, ARM_EXTEND, ARM_EXTEND}};

void motor_op_rot(int motor, int op, int overshoot){
#ifndef NO_GPIO
    assert(motor >= MOTOR_F && motor <= MOTOR_R);
    assert(op >= DIR_CW && op <= DIR_DCW);
    
    if(op >= DIR_DCW){
        if (overshoot) {
            h_turn(motors[motor], op);
        } else {
            h_turn_nos(motors[motor], op);
        }
    } else {
        state.pos[motor] = !state.pos[motor];
        if (overshoot) {
            q_turn(motors[motor], op);
        } else {
            q_turn_nos(motors[motor], op);
        }
    }
    motor_op_reset();
#endif
}

void motor_op_rots(int motor1, int op1, int motor2, int op2, int overshoot){
#ifndef NO_GPIO
    assert(motor1 >= MOTOR_F && motor1 <= MOTOR_R);
    assert(motor2 >= MOTOR_F && motor2 <= MOTOR_R);
    assert(op1 >= DIR_CW && op1 <= DIR_DCW);
    assert(op2 >= DIR_CW && op2 <= DIR_DCW);

    // update state
    if (op1 < DIR_DCW) state.pos[motor1] = !state.pos[motor1];
    if (op2 < DIR_DCW) state.pos[motor2] = !state.pos[motor2];
    
    // Move both motors together.
    if (op1 >= DIR_DCW && op2 >= DIR_DCW) {
        if (overshoot) {
            h_turn_d(motors[motor1], motors[motor2], op1, op2);
        } else {
            h_turn_d_nos(motors[motor1], motors[motor2], op1, op2);
        }
    }
    else {
        if (overshoot) {
            q_turn_d(motors[motor1], motors[motor2], op1, op2);
        } else {
            q_turn_d_nos(motors[motor1], motors[motor2], op1, op2);
        }
        if (op1 >= DIR_DCW) {
            if (overshoot) {
                q_turn(motors[motor1], op1);
            } else {
                q_turn_nos(motors[motor1], op1);
            }
        }
        if (op2 >= DIR_DCW) {
            if (overshoot) {
                q_turn(motors[motor2], op2);
            } else {
                q_turn_nos(motors[motor2], op2);
            }
        }
    }
    motor_op_reset();
#endif
}

void motor_op_arm_move(int arm, int op){
#ifndef NO_GPIO
    assert(arm >= MOTOR_FB && arm <= MOTOR_LR);
    assert(op >= ARM_RETRACT && op <= ARM_EXTEND);

    // calculate distance to new position
    int delta = ARM_OP_STEPS[state.pos[arm]] - ARM_OP_STEPS[op];
    state.pos[arm] = op;
    if(delta != 0) {
        steps(delta, motors[arm]);
    }
    
    // when arms are extended, we always want to have the grippers vertical
    // when they are horizontal, there is risk of collision
    if (op == ARM_EXTEND) {
        if (state.pos[ARM_TO_MOTOR[arm][0]] == G_HORIZ && state.pos[ARM_TO_MOTOR[arm][1]] == G_HORIZ) {
            motor_op_rots(ARM_TO_MOTOR[arm][0], DIR_CW,
                            ARM_TO_MOTOR[arm][1], DIR_CCW);
        } else if (state.pos[ARM_TO_MOTOR[arm][0]] == G_HORIZ) {
            motor_op_rot(ARM_TO_MOTOR[arm][0], DIR_CW);
        } else if (state.pos[ARM_TO_MOTOR[arm][1]] == G_HORIZ) {
            motor_op_rot(ARM_TO_MOTOR[arm][1], DIR_CW);
        }
    }

    motor_op_reset();
#endif
}

void motor_op_arms_move(int arm1, int op1, int arm2, int op2){
#ifndef NO_GPIO
    assert(arm1 >= ARM_FB && arm1 <= ARM_LR);
    assert(arm2 >= ARM_FB && arm2 <= ARM_LR);
    assert(arm1 != arm2);

    // update state
    int delta1 = ARM_OP_STEPS[state.pos[arm1]] - ARM_OP_STEPS[op1];
    int delta2 = ARM_OP_STEPS[state.pos[arm2]] - ARM_OP_STEPS[op2];

    state.pos[arm1] = op1;
    state.pos[arm2] = op2;

    int sign1 = delta1 < 0 ? -1 : 1;
    int sign2 = delta2 < 0 ? -1 : 1;
    
    // move both motors together
    for(int i = 0; i < max(abs(delta1), abs(delta2)); i++){
        if(i < abs(delta1))
            step(sign1 * i, motors[arm1]);
        if(i < abs(delta2))
            step(sign2 * i, motors[arm2]);
        nsleep(DELAY);
    }

    // when arms are extended, we always want to have the grippers vertical
    // when they are horizontal, there is risk of collision
    if (op1 == ARM_EXTEND) {
        if (state.pos[ARM_TO_MOTOR[arm1][0]] == G_HORIZ && state.pos[ARM_TO_MOTOR[arm1][1]] == G_HORIZ) {
            motor_op_rots(ARM_TO_MOTOR[arm1][0], DIR_CW,
                            ARM_TO_MOTOR[arm1][1], DIR_CCW);
        } else if (state.pos[ARM_TO_MOTOR[arm1][0]] == G_HORIZ) {
            motor_op_rot(ARM_TO_MOTOR[arm1][0], DIR_CW);
        } else if (state.pos[ARM_TO_MOTOR[arm1][1]] == G_HORIZ) {
            motor_op_rot(ARM_TO_MOTOR[arm1][1], DIR_CW);
        }
    }

    if (op2 == ARM_EXTEND) {
        if (state.pos[ARM_TO_MOTOR[arm2][0]] == G_HORIZ && state.pos[ARM_TO_MOTOR[arm2][1]] == G_HORIZ) {
            motor_op_rots(ARM_TO_MOTOR[arm2][0], DIR_CW,
                            ARM_TO_MOTOR[arm2][1], DIR_CCW);
        } else if (state.pos[ARM_TO_MOTOR[arm2][0]] == G_HORIZ) {
            motor_op_rot(ARM_TO_MOTOR[arm2][0], DIR_CW);
        } else if (state.pos[ARM_TO_MOTOR[arm2][1]] == G_HORIZ) {
            motor_op_rot(ARM_TO_MOTOR[arm2][1], DIR_CW);
        }
    }

    motor_op_reset();
#endif
}

void motor_op_init(){
#ifndef NO_GPIO
    iolib_init();
    for (int i = 0; i < 6; i++) {
        motor_init(motors[i]);
    }
#endif
}

void motor_op_reset(){
#ifndef NO_GPIO
    for (int i = 0; i < 6; i++) {
        motor_free(motors[i]);
    }
#endif
}

/*
 * Motor Operation: Sequence Execution
 * 
 * Steps to execute a seequence:
 * Consider current operation
 * 1. If exist, perform curr op rot
 * Consider next operation
 * 2. If not exist next op rot, and
 *    curr op face opposes next op face,
 *    perform concurrent motor_op_rots
 * 3. Else, perform motor_op_rot curr
 * 4. Increment op dep. rots/rot
 */
void motor_op_perform_sequence(rubik_sequence_t seq){
    // TODO

}

/*
 * Motor Operation: Face Rotation
 * 
 * Steps to rotate a face:
 * 1. Check if perp grabbers are vertical.
 *    If they are, skip to step 4.
 * 2. Partial extend perp arm.
 * 3. Rotate perp grabbers to vertical.
 * 4. Ensure perp arm is retracted.
 * 5. Ensure parallel arm is retracted.
 * 6. Turn face by direction.
 */

void motor_op_rotate_face(int fmotor, int op){
#ifndef NO_GPIO
    assert(fmotor >= MOTOR_F && fmotor <= MOTOR_R);
    assert(op >= DIR_CW && op <= DIR_DCW);

    // check if perpendicular grabbers are vertical
    if(state.pos[MOTOR_REQ_VERT[fmotor][0]] != G_VERT
    || state.pos[MOTOR_REQ_VERT[fmotor][1]] != G_VERT){
        // make parallel grabbers vertical
        if (state.pos[MOTOR_REQ_VERT_INV[fmotor][0]] == G_HORIZ && state.pos[MOTOR_REQ_VERT_INV[fmotor][1]] == G_HORIZ) {
            motor_op_rots(MOTOR_REQ_VERT_INV[fmotor][0], DIR_CW,
                            MOTOR_REQ_VERT_INV[fmotor][1], DIR_CCW, 0);
        } else if (state.pos[MOTOR_REQ_VERT_INV[fmotor][0]] == G_HORIZ) {
            motor_op_rot(MOTOR_REQ_VERT_INV[fmotor][0], DIR_CW, 0);
        } else if (state.pos[MOTOR_REQ_VERT_INV[fmotor][1]] == G_HORIZ) {
            motor_op_rot(MOTOR_REQ_VERT_INV[fmotor][1], DIR_CW, 0);
        }

        // orient perpendicular grabbers to vertical
        motor_op_arm_move(ROT_ARM[fmotor], ARM_RETRACT);
        motor_op_arm_move(PERP_ARM[fmotor], ARM_PARTIAL);

        // make perpendicular grabbers vertical
        if (state.pos[MOTOR_REQ_VERT[fmotor][0]] == G_HORIZ && state.pos[MOTOR_REQ_VERT[fmotor][1]] == G_HORIZ) {
            motor_op_rots(MOTOR_REQ_VERT[fmotor][0], DIR_CW,
                            MOTOR_REQ_VERT[fmotor][1], DIR_CCW, 0);
        } else if (state.pos[MOTOR_REQ_VERT[fmotor][0]] == G_HORIZ) {
            motor_op_rot(MOTOR_REQ_VERT[fmotor][0], DIR_CW, 0);
        } else if (state.pos[MOTOR_REQ_VERT[fmotor][1]] == G_HORIZ) {
            motor_op_rot(MOTOR_REQ_VERT[fmotor][1], DIR_CW, 0);
        }
    }
    // retract all arms
    motor_op_arm_move(PERP_ARM[fmotor], ARM_RETRACT);
    motor_op_arm_move(ROT_ARM[fmotor], ARM_RETRACT);

    // perform rotation
    motor_op_rot(fmotor, op, 1);
#endif
}

/* 
 * when motor i needs to become the bottom, then
 * turn MOT_A by A[i][MOT_A] and MOT_B
 */
int MOTOR_TO_ROT[4][2] = {
    {R_CW, R_CCW}, // F
    {R_CW, R_CCW}, // B
    {R_CCW, R_CW}, // L
    {R_CCW, R_CW}, // R
};
/*
 * Motor Operation: Cube Rotation
 * 
 * Steps to rotate a cube:
 * If not up or down:
 * 1. Ensure perp arms are retracted
 * 2. Ensure parallel arms are partial extended
 * 3. Rotate perp arms so that side becomes bottom
 * 
 * If up:   do left twice
 * If down: do front twice
 */
void motor_op_rotate_cube(rubik_side_t bottom){
#ifndef NO_GPIO
    if(bottom == R_UP){
        motor_op_rotate_cube(R_LEFT);
        motor_op_rotate_cube(R_LEFT);
    } else if(bottom == R_DOWN){
        motor_op_rotate_cube(R_FRONT);
        motor_op_rotate_cube(R_FRONT);
    } else {
        int smotor = FACE_TO_MOTOR[bottom];
        motor_op_arm_move(PERP_ARM[smotor], ARM_RETRACT);
        motor_op_arm_move(ROT_ARM[smotor], ARM_EXTEND);

        if (state.pos[MOTOR_REQ_VERT_INV[smotor][0]] == G_HORIZ && state.pos[MOTOR_REQ_VERT_INV[smotor][1]] == G_HORIZ) {
            motor_op_rots(MOTOR_REQ_VERT_INV[smotor][0], DIR_CW,
                            MOTOR_REQ_VERT_INV[smotor][1], DIR_CCW, 0);
        } else if (state.pos[MOTOR_REQ_VERT_INV[smotor][0]] == G_HORIZ) {
            motor_op_rot(MOTOR_REQ_VERT_INV[smotor][0], DIR_CW, 0);
        } else if (state.pos[MOTOR_REQ_VERT_INV[smotor][1]] == G_HORIZ) {
            motor_op_rot(MOTOR_REQ_VERT_INV[smotor][1], DIR_CW, 0);
        }

        motor_op_rots(MOTOR_REQ_VERT[smotor][0], MOTOR_TO_ROT[smotor][0],
                        MOTOR_REQ_VERT[smotor][1], MOTOR_TO_ROT[smotor][1], 0);
    }
#endif
}
