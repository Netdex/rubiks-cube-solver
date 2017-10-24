#include <stdio.h>
#include "cube_scanner.h"

int not_main(void) {
    char colours[6] = "WYGBRO";
    int face[3][3] = {0};
    scan_face("../rubik_face.jpg", face);
    printf("%c %c %c\n", colours[face[0][0]], colours[face[0][1]], colours[face[0][2]]);
    printf("%c %c %c\n", colours[face[1][0]], colours[face[1][1]], colours[face[1][2]]);
    printf("%c %c %c\n", colours[face[2][0]], colours[face[2][1]], colours[face[2][2]]);
    return 0;
}
