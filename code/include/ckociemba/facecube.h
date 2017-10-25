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

#ifndef FACECUBE_H
#define FACECUBE_H

#include "ckociemba/facelet.h"
#include "ckociemba/color.h"
#include "ckociemba/corner.h"
#include "ckociemba/edge.h"

//Cube on the facelet level
struct facecube {
    color_t f[54];
};
typedef struct facecube facecube_t;

// forward declaration
struct cubiecube;

// Map the corner positions to facelet positions. cornerFacelet[URF.ordinal()][0] e.g. gives the position of the
// facelet in the URF corner position, which defines the orientation.<br>
// cornerFacelet[URF.ordinal()][1] and cornerFacelet[URF.ordinal()][2] give the position of the other two facelets
// of the URF corner (clockwise).
extern facelet_t cornerFacelet[8][3];

// Map the edge positions to facelet positions. edgeFacelet[UR.ordinal()][0] e.g. gives the position of the facelet in
// the UR edge position, which defines the orientation.<br>
// edgeFacelet[UR.ordinal()][1] gives the position of the other facelet
extern facelet_t edgeFacelet[12][2];

// Map the corner positions to facelet colors.
extern color_t cornerColor[8][3];

// Map the edge positions to facelet colors.
extern color_t edgeColor[12][2];

facecube_t* get_facecube(void);
facecube_t* get_facecube_fromstring(char* cubeString);

void to_String(facecube_t* facecube, char* res);
struct cubiecube* toCubieCube(facecube_t* facecube);

#endif
