#include "ckociemba/search.h"

#include <stdlib.h>
#include "cube/solver.h"

static char* RUBIK_SOLVE_ERROR_MSG[] = {
    "OK",
    "There is not exactly one facelet of each colour",
    "Not all 12 edges exist exactly once",
    "Flip error: One edge has to be flipped",
    "Not all corners exist exactly once",
    "Twist error: One corner has to be twisted",
    "Parity error: Two corners or two edges have to be exchanged",
    "No solution exists for the given maxDepth",
    "Timeout, no solution within given time"
};

rubik_solution_t rubik_solve(rubik_cube_t cube){
    char* facelets = rubik_convert_facelet(cube);
    
    int error = 0;
    // input parameters in ckociemba/facelet.h
	char *sol = solution(
		facelets,
		24,
		1000,
		0,
        "cache",
        &error
    );

    free(facelets);
    
    if(error || !sol){
        rubik_solution_t solt = {error, RUBIK_SOLVE_ERROR_MSG[error]};
        return solt;
    }
    else{
        rubik_sequence_t seq = rubik_make_sequence(sol);
        rubik_solution_t solt = {error, sol, seq};
        return solt;
    }
}

void rubik_destroy_solution(rubik_solution_t *sol){
    free(sol->str);
    rubik_destroy_sequence(&(sol->seq));
}