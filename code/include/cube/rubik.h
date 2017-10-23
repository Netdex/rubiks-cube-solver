#ifndef RUBIK_H
#define RUBIK_H

typedef enum {
   R_W = 0,
   R_G = 1,
   R_O = 2,
   R_Y = 3,
   R_B = 4,
   R_R = 5
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
    R_UP    = 0, 
    R_RIGHT = 1,
    R_FRONT = 2,
    R_DOWN  = 3, 
    R_LEFT  = 4, 
    R_BACK  = 5
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
    rubik_op_t *operations;
} rubik_sequence_t;

/*
 * Builds cube from 6 3x3 matrices of faces.
 * Order of faces is U, R, F, D, L, B.
 */
rubik_cube_t rubik_make_cube(rubik_color_t mat[6][3][3]);
rubik_cube_t rubik_make_cube_from_char(char mat[6][3][3]);
/*
 * Builds a sequence out of an algorithm string.
 * 
 * Operation array is VL, and must be freed through rubik_destroy_sequence
 */
rubik_sequence_t rubik_make_sequence(char *s);
void rubik_destroy_sequence(rubik_sequence_t *t);

/*
 * Convert cube into format compatible with solver API
 */
char* rubik_convert_facelet(rubik_cube_t c);
#endif