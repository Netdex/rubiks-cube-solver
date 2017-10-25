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

#ifndef CUBIECUBE_H
#define CUBIECUBE_H

#include <string.h>
#include <stdlib.h>

#include "ckociemba/corner.h" 
#include "ckociemba/edge.h"

//Cube on the cubie level
struct cubiecube {
    // initialize to Id-Cube
    // corner permutation
    corner_t cp[8];
    // corner orientation
    signed char co[8];
    // edge permutation
    edge_t ep[12];
    // edge orientation
    signed char eo[12];
};
typedef struct cubiecube cubiecube_t;

// forward declaration
struct facecube;

// this CubieCube array represents the 6 basic cube moves
cubiecube_t* get_moveCube(void);
cubiecube_t* get_cubiecube(void);

// n choose k
int Cnk(int n, int k);
void rotateLeft_corner(corner_t* arr, int l, int r);
void rotateRight_corner(corner_t* arr, int l, int r);
void rotateLeft_edge(edge_t* arr, int l, int r);
void rotateRight_edge(edge_t* arr, int l, int r);
struct facecube* toFaceCube(cubiecube_t* cubiecube);
void cornerMultiply(cubiecube_t* cubiecube, cubiecube_t* b);
void edgeMultiply(cubiecube_t* cubiecube, cubiecube_t* b);
void multiply(cubiecube_t* cubiecube, cubiecube_t* b);
void invCubieCube(cubiecube_t* cubiecube, cubiecube_t* c);
short getTwist(cubiecube_t* cubiecube);
void setTwist(cubiecube_t* cubiecube, short twist);
short getFlip(cubiecube_t* cubiecube);
void setFlip(cubiecube_t* cubiecube, short flip);
short cornerParity(cubiecube_t* cubiecube);
short edgeParity(cubiecube_t* cubiecube);
short getFRtoBR(cubiecube_t* cubiecube);
void setFRtoBR(cubiecube_t* cubiecube, short idx);
short getURFtoDLF(cubiecube_t* cubiecube);
void setURFtoDLF(cubiecube_t* cubiecube, short idx);
int getURtoDF(cubiecube_t* cubiecube);
void setURtoDF(cubiecube_t* cubiecube, int idx);

short getURtoUL(cubiecube_t* cubiecube);
void setURtoUL(cubiecube_t* cubiecube, short idx);
short getUBtoDF(cubiecube_t* cubiecube);
void setUBtoDF(cubiecube_t* cubiecube, short idx);
int getURFtoDLB(cubiecube_t* cubiecube);
void setURFtoDLB(cubiecube_t* cubiecube, int idx);
int getURtoBR(cubiecube_t* cubiecube);
void setURtoBR(cubiecube_t* cubiecube, int idx);

int verify(cubiecube_t* cubiecube);

int getURtoDF_standalone(short idx1, short idx2);

#endif
