#include "ckociemba/search.h"

#include <stdlib.h>
#include "cube/solver.h"


rubik_solution_t rubik_solve(rubik_cube_t cube){
    char* facelets = rubik_convert_facelet(cube);
    
    // input parameters in ckociemba/facelet.h
	char *sol = solution(
		facelets,
		24,
		1000,
		0,
		"cache"
    );
    if(!sol){
        rubik_solution_t solt = {false, "no solution"};
        return solt;
    }
    else{
        free(facelets);
        rubik_sequence_t seq = rubik_make_sequence(sol);
        rubik_solution_t solt = {true, sol, seq};
        return solt;
    }
}

void rubik_destroy_solution(rubik_solution_t *sol){
    free(sol->solution_str);
    rubik_destroy_sequence(&(sol->solution_seq));
}