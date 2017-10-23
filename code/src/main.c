#include <stdio.h>

#include "cube/rubik.h"
#include "cube/solver.h"

int main(const int argc, const char *argv[]){
    char cube_mat[6][3][3];
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                scanf("%c", &cube_mat[f][y][x]);
            }
        }
    }
    rubik_cube_t cube = rubik_make_cube_from_char(cube_mat);
    rubik_solution_t solution = rubik_solve(cube);
    printf("%d | %s\n", solution.error_code, solution.str);
	return 0;

}
