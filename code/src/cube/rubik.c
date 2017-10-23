#include "cube/rubik.h"

static rubik_color_t rubik_char_to_color(char c){
    switch(c){
        case 'R': return R_RED;
        case 'O': return R_ORANGE;
        case 'B': return R_BLUE;
        case 'G': return R_GREEN;
        case 'W': return R_WHITE;
        case 'Y': return R_YELLOW;
        default: return R_WHITE;
    }
}
rubik_cube_t rubik_make_cube(char mat[6][3][3]){
    rubik_cube_t c;
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                c.faces[f].colors[y][x] = rubik_char_to_color(mat[f][y][x]);
            }
        }
    }
    return c;
}

// rubik_sequence_t rubik_make_sequence(const char *s){
    
// }