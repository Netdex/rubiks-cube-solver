#include "stdafx.h"
#include "motor_op.h"
#include "motor.h"

/* DOCUMENTATION IS IN motor_op.h */

/* map rubik_face_t to appropriate motor */
int FACE_TO_MOTOR[] = {-1, 3, 0, -1, 2, 1};
/* index i, is motor steps to achieve operation i */
const int ARM_OP_STEPS[] = {0, 1900, 2900};
/* grabbers A[i] must be vertical when doing a rotation on face i */
int MOTOR_REQ_VERT[4][2] = {
    {MOTOR_L, MOTOR_R},     // F
    {MOTOR_L, MOTOR_R},     // B
    {MOTOR_F, MOTOR_B},     // L
    {MOTOR_F, MOTOR_B}      // R
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
        // (vertical = 0, horizontal = 0)
        int f;      // position of front grabber
        int b;      // position of back grabber
        int l;      // position of left grabber
        int r;      // position of right grabber
        // (retracted = 0, partial = 1, extended = 2)
        int fb;     // position of f/b arm
        int lr;     // position of l/r arm
    };
    int pos[6];    // grabber positions
} state = {{0, 0, 0, 0, 0, 0}};


void motor_op_rot(int motor, int op){
    state.pos[motor] = !state.pos[motor];
    q_turn(motors[motor], op);
}

void motor_op_rots(int motor1, int op1, int motor2, int op2){
    // TODO
}

void motor_op_arm_move(int arm, int op){
    int delta = ARM_OP_STEPS[state.pos[arm]] - ARM_OP_STEPS[op];
    state.pos[arm] = op;
    if(delta != 0) {
        steps(delta, motors[arm]);
    }
}

void motor_op_arms_move(int arm1, int op1, int arm2, int op2){
    int delta1 = ARM_OP_STEPS[state.pos[arm1]] - ARM_OP_STEPS[op1];
    int delta2 = ARM_OP_STEPS[state.pos[arm2]] - ARM_OP_STEPS[op2];

    int sign1 = delta1 < 0 ? -1 : 1;
    int sign2 = delta2 < 0 ? -1 : 1;
    
    // move both motors together
    for(int i = 0; i < max(abs(delta1), abs(delta2)); i++){
        if(i < abs(delta1))
            step(sign1 * i, motors[arm1]);
        if(i < abs(delta2))
            step(sign2 * i, motors[arm2]);
    }
}

void motor_op_init(){
    LOG("initializing motors...");
    iolib_init();
    for (int i = 0; i < 6; i++) {
        motor_init(motors[i]);
    }
}

void motor_op_reset(){
    LOG("resetting motors...");
    for (int i = 0; i < 6; i++) {
        motor_free(motors[i]);
    }
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
void motor_op_rotate_face(rubik_side_t face, rubik_dir_t dir){
    assert(face != R_UP && face != R_DOWN);
    if(face == R_NOSIDE)    return;
    if(dir == R_NODIR)      return;

    // motor corresponding to face we want to rotate
    int dmotor = FACE_TO_MOTOR[face];
    
    // check if perpendicular grabbers are vertical
    if(state.pos[MOTOR_REQ_VERT[dmotor][0]] != G_VERT
    || state.pos[MOTOR_REQ_VERT[dmotor][1]] != G_VERT){
        // orient perpendicular grabbers to vertical
        motor_op_arm_move(PERP_ARM[dmotor], ARM_PARTIAL);
        for(int i = 0; i < 2; i++){
            if(state.pos[MOTOR_REQ_VERT[dmotor][i] != G_VERT])
                motor_op_rot(MOTOR_REQ_VERT[dmotor][i], DIR_CW);
        }
    }
    // retract all arms
    motor_op_arm_move(PERP_ARM[dmotor], ARM_RETRACT);
    motor_op_arm_move(ROT_ARM[dmotor], ARM_RETRACT);

    // perform rotation
    if(dir == R_DOUBLE_CW){
        motor_op_rot(dmotor, DIR_CW);
        motor_op_rot(dmotor, DIR_CW);
    }
    else {
        motor_op_rot(dmotor, (int) dir);
    }
}


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
    if(bottom == R_UP){

    } else if(bottom == R_DOWN){
        
    } else {
        int smotor = FACE_TO_MOTOR[bottom];
        motor_op_arms_move(PERP_ARM[smotor], ARM_RETRACT, ROT_ARM[smotor], ARM_EXTEND);
        // motor_op_rots(...)
    }
}
