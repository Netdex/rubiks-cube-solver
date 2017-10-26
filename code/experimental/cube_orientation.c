// #include <stdlib.h>
//
// #include "cube/rubik.h"
//
// // rubik_solution_t cube_orientation(rubik_solution_t cube){
// //   // Reparsing the solution to make it compatible with the 4 arms
// //   // Rotations can only work turning clockwise/counterclockwise front back
// //   // OR by turning clokwise/counterclockwise right left
// //   for(int i = 0; i < cube.seq.length; i++){
// //     // 1) We must rotate the cube if an operation has to be done to the top or the bottom of the cube
// //     // 2) We also want to optimize the number of steps
// //     if (cube.seq.operations[i].side == R_UP || cube.seq.operations[i].side == R_DOWN){
// //       // create a list of next steps to see which one will be affected more (we want to reduce number of rotations)
// //     }
// //   }
// //
// // }
// // Basically add a new command to tell the solver to either rotate the cube to the front or to the side
// // Base cases - Reach the end of the string of commands, modifies it as required. then outputs
//
//
// // Parses sequence to create a solver friendly solution that takes away all top and bottom turns buy turning the cube to a solvable state
// rubik_sequence_t remove_up_down(rubik_sequence_t *s){
//   int l = 0;
//   for(int i = 0; s[i]; i++)
//       if(s[i] == ' ') ++l;
//   int opc = 0, idx = 0;
//   rubik_op_t *ops = calloc(l+20, sizeof(rubik_op_t));
//   for(int i = 0; s[i];){
//       rubik_op_t cop = {0};
//       if (s[i].side == R_UP || s[i].side == R_DOWN){
//         for(int j = i; s[j];){
//           switch(s[j].side){
//             case R_UP:    s[j].side = R_FRONT;  break;
//             case R_RIGHT: s[j].side = R_RIGHT;  break;
//             case R_FRONT: s[j].side = R_DOWN;   break;
//             case R_DOWN:  s[j].side = R_BACK;   break;
//             case R_LEFT:  s[j].side = R_LEFT;   break;
//             case R_BACK:  s[j].side = R_UP;     break;
//             }
//           }
//           // Adds a turning mechanism
//           cop.side = R_NOSIDE;
//           cop.direction = R_NODIR;
//           cop.rotation = R_FONB;
//           ops[opc++] = cop;
//       }
//       // Add next step
//       cop.side = s[i].side;
//       cop.direction = s[i].direction;
//       ops[opc++] = cop;
//   }
//   rubik_sequence_t seq = {l, ops};
//   return seq;
// }
