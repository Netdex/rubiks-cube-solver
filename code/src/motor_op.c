#include "stdafx.h"
#include "motor_op.h"
#include "motor.h"

/* DOCUMENTATION IS IN motor_op.h */

/* map rubik_face_t to appropriate motor */
int FACE_TO_MOTOR[] = {-1, 3, 0, -1, 2, 1};

/* GPIO pinout for motors */
motor motors[] = {
    {43, 44, 45, 46}, // F
    {7, 8, 9, 10},    // B
    {39, 40, 41, 42}, // L
    {15, 16, 17, 18}, // R
    {11, 12, 13, 14}, // F/B retract/extend
    {35, 36, 37, 38}, // L/R retract/extend
};

/* motor position state for optimizing moves */
struct motor_op_state {
    // (vertical = 0, horizontal = 0)
    union {
        struct {
            int f;      // position of front grabber
            int b;      // position of back grabber
            int l;      // position of left grabber
            int r;      // position of right grabber
            int fb;     // position of f/b arm
            int lr;     // position of l/r arm
        };
        int pos[6];    // grabber positions
    };
} state = {0, 0, 0, 0, 0, 0};


void motor_op_rot(int motor, int op){
    state.pos[motor] = !state.pos[motor];
    q_turn(motors[motor], op);
}

void motor_op_arm_move(int arm, int op){
    int delta = ARM_OP_STEPS[state.pos[arm]] - ARM_OP_STEPS[op];
    state.pos[arm] = op;
    if(delta != 0) {
        steps(delta, motors[arm]);
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

}
