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

#ifndef COLOR_H
#define COLOR_H
// Names the colors of the cube facelets
typedef enum {U, R, F, D, L, B} color_t;

#define COLOR_COUNT 6
#endif
