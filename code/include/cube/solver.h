#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>

#include "cube/rubik.h"
#include "ckociemba/search.h"

typedef struct {
    bool has_solution;
    char* str;
    rubik_sequence_t seq;
} rubik_solution_t;

rubik_solution_t rubik_solve(rubik_cube_t cube);
void rubik_destroy_solution(rubik_solution_t *sol);
#endif