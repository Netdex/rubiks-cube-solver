#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "cube_scanner.h"
#include "bbb_gpio.h"
#include "cube/rubik.h"
#include "cube/solver.h"

void test_kmeans();

int main(void) {
    // srand((unsigned int)time(NULL));

    // test_kmeans();
    // char colours[6] = "WYGBRO";
    // int face[3][3] = {0};

    // for (int i = 0; i < 20; i++) {
    //     system("fswebcam --device /dev/video1 -q -r 640x360 --no-banner -S 30 temp.jpg");
    //     scan_face("temp.jpg", face);
    //     printf("\033[F\033[J\033[F\033[J\033[F\033[J");
    //     printf("%c %c %c\n", colours[face[0][0]], colours[face[0][1]], colours[face[0][2]]);
    //     printf("%c %c %c\n", colours[face[1][0]], colours[face[1][1]], colours[face[1][2]]);
    //     printf("%c %c %c\n", colours[face[2][0]], colours[face[2][1]], colours[face[2][2]]);
    // }
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
