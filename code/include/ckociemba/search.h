/*
 *   ckociemba - pure c implementation of Kociemba's two-phase algorithm for solving a Rubik's cube
 *   Copyright (C) 2017 muodov
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEARCH_H
#define SEARCH_H

typedef struct {
    int ax[31];             // The axis of the move
    int po[31];             // The power of the move
    int flip[31];           // phase1 coordinates
    int twist[31];
    int slice[31];
    int parity[31];         // phase2 coordinates
    int URFtoDLF[31];
    int FRtoBR[31];
    int URtoUL[31];
    int UBtoDF[31];
    int URtoDF[31];
    int minDistPhase1[31];  // IDA* distance do goal estimations
    int minDistPhase2[31];
} search_t;

search_t* get_search(void);

// generate the solution string from the array data including a separator between phase1 and phase2 moves
char* solutionToString(search_t* search, int length, int depthPhase1);
/**
 * Computes the solver string for a given cube.
 * 
 * @param facelets
 *          is the cube definition string, see {@link Facelet} for the format.
 * 
 * @param maxDepth
 *          defines the maximal allowed maneuver length. For random cubes, a maxDepth of 21 usually will return a
 *          solution in less than 0.5 seconds. With a maxDepth of 20 it takes a few seconds on average to find a
 *          solution, but it may take much longer for specific cubes.
 * 
 *@param timeOut
 *          defines the maximum computing time of the method in seconds. If it does not return with a solution, it returns with
 *          an error code.
 * 
 * @param useSeparator
 *          determines if a " . " separates the phase1 and phase2 parts of the solver string like in F' R B R L2 F .
 *          U2 U D for example.<br>
 * @return The solution string or an error code:<br>
 *         Error 1: There is not exactly one facelet of each colour<br>
 *         Error 2: Not all 12 edges exist exactly once<br>
 *         Error 3: Flip error: One edge has to be flipped<br>
 *         Error 4: Not all corners exist exactly once<br>
 *         Error 5: Twist error: One corner has to be twisted<br>
 *         Error 6: Parity error: Two corners or two edges have to be exchanged<br>
 *         Error 7: No solution exists for the given maxDepth<br>
 *         Error 8: Timeout, no solution within given time
 */
char* solution(char* facelets, int maxDepth, long timeOut, int useSeparator, const char* cache_dir, int *e);

// Apply phase2 of algorithm and return the combined phase1 and phase2 depth. In phase2, only the moves
// U,D,R2,F2,L2 and B2 are allowed.
int totalDepth(search_t* search, int depthPhase1, int maxDepth);


// Add a pattern to the state of a cube, so that the solution for new_facelets
// applied to facelets will result into the given pattern
void patternize(char* facelets, char* pattern, char* patternized);

#endif
