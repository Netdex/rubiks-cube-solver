#include <stdlib.h>

#include "cube/rubik.h"
#include "util/log.h"

static rubik_color_t rubik_char_to_color(char c){
    switch(c){
        case 'R':   return R_R;
        case 'O':   return R_O;
        case 'B':   return R_B;
        case 'G':   return R_G;
        case 'W':   return R_W;
        case 'Y':   return R_Y;
        default:
            LOG("invalid cube face color");  
            return R_W;
    }
}

static char rubik_to_face_char(rubik_color_t c){
    switch(c){
        case R_W:   return 'U';
        case R_G:   return 'R';
        case R_O:   return 'F';
        case R_Y:   return 'D';
        case R_B:   return 'L';
        case R_R:   return 'B';
        default:
            LOG("invaid cube face color");
            return ' ';
    }
}

rubik_cube_t rubik_make_cube(rubik_color_t mat[6][3][3]){
    rubik_cube_t c;
    for(int f = 0; f < 6; f++)
        for(int y = 0; y < 3; y++)
            for(int x = 0; x < 3; x++)
                c.faces[f].colors[y][x] = mat[f][y][x];
    return c;
}

rubik_cube_t rubik_make_cube_from_char(char mat[6][3][3]){
    rubik_color_t cmat[6][3][3];
    for(int f = 0; f < 6; f++)
        for(int y = 0; y < 3; y++)
            for(int x = 0; x < 3; x++)
                cmat[f][y][x] = rubik_char_to_color(mat[f][y][x]);
    return rubik_make_cube(cmat);
}

rubik_sequence_t rubik_make_sequence(char *s){
    int l = 0;
    for(int i = 0; s[i]; i++)
        if(s[i] == ' ') ++l;

    int opc = 0;
    rubik_op_t *ops = calloc(l, sizeof(rubik_op_t));
    for(int i = 0; s[i];){
        rubik_op_t cop = {0};
        switch(s[i]){
            case 'U':   cop.side = R_UP;      break;
            case 'R':   cop.side = R_RIGHT;   break;
            case 'F':   cop.side = R_FRONT;   break;
            case 'D':   cop.side = R_DOWN;    break;
            case 'L':   cop.side = R_LEFT;    break;
            case 'B':   cop.side = R_BACK;    break;
        }
        switch(s[i + 1]){
            case ' ':
                cop.direction = R_CW;
                i += 2;
            break;
            case '\'':
                cop.direction = R_CCW;
                i += 3;
            break;
            case '2':
                cop.direction = R_DOUBLE_CW;
                i += 3;
            break;
        }
        ops[opc++] = cop;
    }

    rubik_sequence_t seq = {l, ops};
    return seq;
}

void rubik_destroy_sequence(rubik_sequence_t *t){
    free(t->operations);
}

char* rubik_sequence_to_string(rubik_sequence_t *t){
    char* str = calloc(t->length * 3 + 1, 1);
    int p = 0;
    for(int i = 0; i < t->length; i++){
        switch(t->operations[i].side){
            case R_UP:      str[p++] = 'U'; break;
            case R_RIGHT:   str[p++] = 'R'; break;
            case R_FRONT:   str[p++] = 'F'; break;
            case R_DOWN:    str[p++] = 'D'; break;
            case R_LEFT:    str[p++] = 'L'; break;
            case R_BACK:    str[p++] = 'B'; break;
        }
        switch(t->operations[i].direction){
            case R_CW:          str[p++] = ' ';     break;
            case R_CCW:         str[p++] = '\'';    str[p++] = ' ';   break;
            case R_DOUBLE_CW:   str[p++] = '2';     str[p++] = ' ';   break;
        }
    }
    return str;
}
char* rubik_convert_facelet(rubik_cube_t c){
    char *str = malloc(9 * 6 + 1);
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                str[f * 9 + y * 3 + x] 
                    = rubik_to_face_char(c.faces[f].colors[y][x]);
            }
        }
    }
    return str;
}