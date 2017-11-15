#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <BBBiolib.h>
#include "cube_scanner.h"
<<<<<<< HEAD
#include "bbb_gpio.h"
#include "cube/rubik.h"
#include "cube/solver.h"
=======
#include "lcd.h"
#include "motor.h"
>>>>>>> 9e10252d0dd8aebbadfbbed4fe18c5842e3d6da2

void test_kmeans();

int main(void) {
<<<<<<< HEAD
    // srand((unsigned int)time(NULL));

    // test_kmeans();
=======
    //srand((unsigned int)time(NULL));

    //test_kmeans();
>>>>>>> 9e10252d0dd8aebbadfbbed4fe18c5842e3d6da2
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
<<<<<<< HEAD
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
=======

    /*lcd l = {66, 67, 69, 68, 45, 44};
    lcd_init(l);
    
    write_string(l, "F");
    nsleep(2000000000);
    write_string(l, "R'");
    nsleep(2000000000);
    write_string(l, "U2");
    nsleep(2000000000);
    write_string(l, "B'");
    nsleep(2000000000);
    write_string(l, "F");
    nsleep(2000000000);
    write_string(l, "L");
    nsleep(2000000000);*/

    iolib_init();

    motor m = {13, 14, 15, 16};
    motor_init(m);
    for(int i = 0; i < 200; i++) {
        step(i, m);
        nsleep(750000);
    }

    iolib_free();
    
>>>>>>> 9e10252d0dd8aebbadfbbed4fe18c5842e3d6da2
    return 0;
}
