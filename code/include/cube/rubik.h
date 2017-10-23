#ifndef RUBIK_H
#define RUBIK_H

typedef enum {
    R_RED, R_ORANGE, R_BLUE, R_GREEN, R_WHITE, R_YELLOW
} rubik_color_t;

typedef struct {
    rubik_color_t colors[3][3];
} rubik_face_t;

typedef struct {
    union {
        struct{
            rubik_face_t U, R, F, D, L, B;
        };
        rubik_face_t faces[6];
    };
} rubik_cube_t;

typedef enum {
    R_UP, R_DOWN, R_LEFT, R_RIGHT, R_FRONT, R_BACK
} rubik_side_t;

typedef enum {
    R_CW = 1, 
    R_CCW = -1, 
    R_DOUBLE_CW = 2
} rubik_dir_t;

/* elementary rubik's cube operation */
typedef struct {
    rubik_side_t side;
    /* M': -1, M: 1, M2: 2 */
    rubik_dir_t direction;
} rubik_op_t;

/* sequence of rubik's cube operations */
typedef struct {
    int length;
    rubik_op_t operations[];
} rubik_sequence_t;

/*
 * Builds cube from 6 3x3 matrices of characters.
 * Order of faces is U, R, F, D, L, B.
 */
rubik_cube_t rubik_make_cube(char mat[6][3][3]);

rubik_sequence_t rubik_make_sequence(const char *s);
#endif