#include <stdio.h>

#include "cube/rubik.h"
#include "cube/solver.h"

int main(const int argc, const char *argv[]){
    char cube_mat[6][3][3] = {
        {               // UP
            {'Y','W','W'},
            {'G','W','Y'},
            {'W','R','Y'},
        },
        {               // RIGHT
            {'B','B','G'},
            {'B','G','B'},
            {'R','O','B'},
        },
        {               // FRONT
            {'G','G','O'},
            {'O','O','O'},
            {'B','G','G'},
        },
        {               // DOWN
            {'W','W','Y'},
            {'W','Y','Y'},
            {'Y','Y','W'},
        },
        {               // LEFT
            {'O','Y','O'},
            {'W','B','G'},
            {'B','R','O'},
        },
        {               // BACK
            {'R','B','G'},
            {'R','R','O'},
            {'R','R','R'},
        }
    };
    rubik_cube_t cube = rubik_make_cube_from_char(cube_mat);
    rubik_solution_t solution = rubik_solve(cube);
    printf("%s\n", solution.str);
    printf("%s\n", rubik_sequence_to_string(&solution.seq));
	return 0;

}
