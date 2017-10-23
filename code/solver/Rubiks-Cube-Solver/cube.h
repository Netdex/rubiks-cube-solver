/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Copyright © 2009 Andrew Brown <brownan@gmail.com>
*/
#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>

/**
 * The cube type.  This is made up of a 40 byte string, broken up into
 * substrings of length 2, one substring for each of the 20 cubies as shown in
 * the diagram below.
 * Each substring consists of:
 * 1) an integer between 0 and 19 indicating its position
 * 2) an integer between 0 and 2 for corner cubies and between 0 and 1 for edge
 * cubies indicating the rotation of that piece
 *
 * Cubies are numbered from 0 to 19 throughout the code, as shown here 
    5----6----7
    |         |\
    3    Y    4 \
    |         |  \
    0----1----2   \
     \             \
      \   10---R---11
       \  |         |\
        \ B    X    G \
         \|         |  \
          8----O----9   \
           \             \
            \   17--18---19
             \  |         |
              \ 15   W   16
               \|         |
                12--13---14

 * Rotations are defined thusly:
 * For corner cubies:
 *  It is defined to have a rotation of 0 if the white or yellow face
 *  of the cubie is facing front or back.
 *  It is defined to have a rotation of 1 if the white or yellow face
 *  of the cubie is facing left or right.
 *  It is defined to have a rotation of 2 if the white or yellow face
 *  of the cubie is facing up or down.
 * For edge cubies:
 *  All edge cubies have a rotation of 0 in their solved state.  The
 *  rotation of an edge cubie is toggled when it is present on either
 *  the left or the right face, and that face experiences a quarter turn.
 *  Otherwise, the edge rotation remains the same.
 *  (Try it, you cannot change the orientation of an edge piece without
 *  rotating the left or right sides in quarter turns! Neat!)
 */
#define CUBELEN 40
typedef char cube_type[CUBELEN];

extern const char cube_solved[];

/*
 * This macro is used to return a pointer into a cube type for the given cubie
 * (sub-cube).
 */
#define CUBIE(cube, n) ((char *)cube + (n << 1))

/*
 * Defines cube sides, they go in this order
 */
#define FRONT 0
#define TOP 1
#define LEFT 2
#define BACK 3
#define DOWN 4
#define RIGHT 5

int cube_120convert(const char *input, char *output);

char *cube_turn(char *to_twist, int direction);

/*
 * This table is used in the heuristics.  For each twist, there are certian
 * twists that should be subsequently avoided.  This helps avoid the situation
 * of turning opposite faces in a different order.  In short, when a turn is
 * performed, this table should be consulted for turns that should NOT be
 * performed right after.
 *
 * The table works like this: 
 * cube_turn_avoid is an array, the Mth bit of the Nth item indicates that turn
 * M should not be performed after turning the cube in the N direction.
 * 
 * So to determine if you should turn a direction i after having turned a
 * direction t, do:
 * if (cube_turn_avoid[t] & (1L << i)) {...}
 * in fact, I think I'll make that a macro:
 */
#define SHOULDIAVOID(i, t) (cube_turn_avoid[t] & (1L<<i))
/*
 * Now just do:
 * if (SHOULDIAVOID(i, t)) {...}
 * the macro returns TRUE if you should NOT take that path
 *
 * Side note: these numbers should be at least 18 bits.  An integer is usually
 * 32 bits, but not guaranteed to be so, so I use long here instead.
 *
 * This is defined in cube.c, delcared here.
 */
extern const long cube_turn_avoid[];

int cube_print(FILE *output, const char *cube);

#endif
