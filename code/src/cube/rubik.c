#include "stdafx.h"

#include <stdlib.h>

#include "cube/rubik.h"
#include "util/log.h"

char RUBIK_MAP_FACE_CHAR[]  = {'U', 'R', 'F', 'D', 'L', 'B'};
char RUBIK_MAP_ROT_CHAR[]   = {'x', 'r', 'f', 'd', 'l', 'y'};
char RUBIK_MAP_DIR_CHAR[]   = {' ', '\'', '2'};

static rubik_color_t rubik_char_to_color(char c){
    switch(c){
        case 'R':   return R_F;
        case 'O':   return R_B;
        case 'B':   return R_L;
        case 'G':   return R_R;
        case 'W':   return R_U;
        case 'Y':   return R_D;
        default:
            LOG("invalid cube face color");
            return R_U;
    }
}

static char rubik_to_face_char(rubik_cube_t *cube, rubik_color_t c){
    if(c == cube->U.colors[1][1]) return 'U';
    if(c == cube->R.colors[1][1]) return 'R';
    if(c == cube->F.colors[1][1]) return 'F';
    if(c == cube->D.colors[1][1]) return 'D';
    if(c == cube->L.colors[1][1]) return 'L';
    if(c == cube->B.colors[1][1]) return 'B';
    LOG("invaid cube face color");
    return ' ';
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
        cop.rotation = R_NOSIDE;
        ops[opc++] = cop;
    }

    rubik_sequence_t seq = {l, ops};
    return seq;
}

void rubik_destroy_sequence(rubik_sequence_t *t){
    free(t->operations);
}

char* rubik_sequence_to_string(rubik_sequence_t *t){
    char* str = calloc(t->length * 4 + 1, 1);
    int p = 0;
    for(int i = 0; i < t->length; i++){
        switch(t->operations[i].rotation){
            case R_FRONT:   str[p++] = 'f';  break;
            case R_BACK:    str[p++] = 'b';  break;
            case R_RIGHT:   str[p++] = 'r';  break;
            case R_LEFT:    str[p++] = 'l';  break;
            case R_UP:      str[p++] = 'x';  break;
            case R_DOWN:    str[p++] = 'z';  break;
            default: break;
        }
        switch(t->operations[i].side){
            case R_UP:      str[p++] = 'U'; break;
            case R_RIGHT:   str[p++] = 'R'; break;
            case R_FRONT:   str[p++] = 'F'; break;
            case R_DOWN:    str[p++] = 'D'; break;
            case R_LEFT:    str[p++] = 'L'; break;
            case R_BACK:    str[p++] = 'B'; break;
            case R_NOSIDE:  str[p++] = '_'; break;
        }
        switch(t->operations[i].direction){
            case R_CW:          str[p++] = ' ';     break;
            case R_CCW:         str[p++] = '\'';    str[p++] = ' ';   break;
            case R_DOUBLE_CW:   str[p++] = '2';     str[p++] = ' ';   break;
            case R_NODIR:       str[p++] = '_';      str[p++] = ' ';   break;
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
                    = rubik_to_face_char(&c, c.faces[f].colors[y][x]);
            }
        }
    }
    return str;
}

rubik_face_t rubik_face_rotate(rubik_face_t face, rubik_dir_t dir){
    switch(dir){
        case R_CCW:         return rubik_face_rotate(rubik_face_rotate(face, R_CW), R_DOUBLE_CW);
        case R_DOUBLE_CW:   return rubik_face_rotate(rubik_face_rotate(face, R_CW), R_CW);
        case R_CW:      
        {
            rubik_face_t rot = {
                {
                    {face.colors[2][0],face.colors[1][0],face.colors[0][0]},
                    {face.colors[2][1],face.colors[1][1],face.colors[0][1]},
                    {face.colors[2][2],face.colors[1][2],face.colors[0][2]}
                }
            };
            return rot;
        } 
        default: return face;
    }
}

rubik_sequence_t rubik_cube_remove_up_down(rubik_sequence_t *s){
    // this is not an optimized solution.
    int l = s->length;

    rubik_op_t *ops = malloc(l * sizeof(rubik_op_t));
    memcpy(ops, s->operations, l * sizeof(rubik_op_t));
    rubik_sequence_t seq = {l, ops};
    for(int i = 0; i < seq.length; i++){

        // don't run this algorithm twice
        assert(ops[i].rotation == R_NOSIDE);

        if(ops[i].side == R_UP || ops[i].side == R_DOWN){
            rubik_sequence_rotate(&seq, i, seq.length - i, R_RIGHT);
            ops[i].rotation = R_RIGHT;
        }
    }
    return seq;
}

/* 
 * Mapping that maps a face j after a rotation i 
 * to face RUBIK_ROTATION_MATRIX[i][j] 
 * 
 * TODO: check for mistakes
 */
const char RUBIK_ROTATION_MATRIX[6][6] = {
    {3, 1, 5, 0, 4, 2},  // U
    {1, 3, 2, 4, 0, 5},  // R
    {2, 1, 3, 5, 4, 0},  // F
    {3, 4, 2, 0, 1, 5},  // D
    {4, 0, 2, 1, 3, 5},  // L
    {5, 1, 0, 2, 4, 3},  // B
};

void rubik_sequence_rotate(rubik_sequence_t *s, int idx, int len, rubik_side_t bottom){
    assert(idx + len <= s->length);
    for(int i = idx; i < idx + len; i++){
        s->operations[i].side = RUBIK_ROTATION_MATRIX[bottom][s->operations[i].side];
    }
}