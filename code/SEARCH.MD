# Search Plan
## Elementary Operations and Requirements

Note: for directions, only CW and CCW are required/allowed.

#### Notation:
- F: Front motor
- B: Back motor
- L: Left motor
- R: Right motor

- FB: Front/back arm motor
- LR: Left/right arm motor

Let M be a motor, A be an arm.
- [M]: Perpendicular motors
- [M: Left perpendicular motor
- M]: Right perpendicular motor
- /M/: Parallel motors
- /M: Opposite parallel motor
- //A: Parallel arm motor
- /-A: Perpendicular arm motor

### Rotate face
`bool valid_face_rotate(int motor, int dir, bool mutate_cube_allowed)`

Q: Can we move this motor in this direction?

#### Requirements:
- [M] vertical
- /-A retract

mutate_cube_allowed:
- //A retract
else
- //A extend

### Rotate faces simulatenously
`bool valid_faces_rotate(int motor1, int dir1, int motor2, int dir2, bool mutate_cube_allowed),`

Q: Can we move these motors simultaneously in these respective directions?

#### Requirements:
- M1 opposite M2
- [M] vertical
- /-A1 retract

mutate_cube_allowed:
- //A retract
else
- //A extend

### Extend arm
`bool valid_arm_fb_move(int motor, int op)`

Q: Can we move this arm to this position?

#### Requirements:
- /-A 
### Extend arms simulatenously
`bool valid_arm_fb_move(int motor1, int op1, int motor2, int op2)`

Q: Can we move these arms simulataneously to these respective positions?

## Search Start and Termination Condition
Start at current cube state. Only allow operations that do not mutate cube state. The termination condition is that the respective cube mutation is allowed.
