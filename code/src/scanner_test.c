#include <stdio.h>
#include <stdlib.h>
#include "cube_scanner.h"

int not_main(void) {
    char colours[6] = "WYGBRO";
    int face[3][3] = {0};
    for (int i = 0; i < 20; i++) {
        system("fswebcam --device /dev/video1 -q -r 640x360 --no-banner -S 30 temp.jpg");
        scan_face("temp.jpg", face);
        printf("\033[F\033[J\033[F\033[J\033[F\033[J");
        printf("%c %c %c\n", colours[face[0][0]], colours[face[0][1]], colours[face[0][2]]);
        printf("%c %c %c\n", colours[face[1][0]], colours[face[1][1]], colours[face[1][2]]);
        printf("%c %c %c\n", colours[face[2][0]], colours[face[2][1]], colours[face[2][2]]);
    }
    return 0;
}
