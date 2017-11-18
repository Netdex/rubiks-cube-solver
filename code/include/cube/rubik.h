#ifndef RUBIK_H
#define RUBIK_H

extern char RUBIK_MAP_FACE_CHAR[];
extern char RUBIK_MAP_ROT_CHAR[];
extern char RUBIK_MAP_DIR_CHAR[];

typedef enum {
   R_U = 0,
   R_R = 1,
   R_F = 2,
   R_D = 3,
   R_L = 4,
   R_B = 5
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
    R_NOSIDE    = -1,
    R_UP        = 0,
    R_RIGHT     = 1,
    R_FRONT     = 2,
    R_DOWN      = 3,
    R_LEFT      = 4,
    R_BACK      = 5,
} rubik_side_t;

typedef enum {
    R_NODIR     = -1,
    R_CW        = 0,
    R_CCW       = 1,
    R_DOUBLE_CW = 2,
} rubik_dir_t;

/* elementary rubik's cube operation */
typedef struct {
    rubik_side_t side;
    /* M': -1, M: 1, M2: 2 */
    rubik_dir_t direction;

    /* the side that will become the bottom after the rotation */
    rubik_side_t rotation;
} rubik_op_t;

/* sequence of rubik's cube operations */
typedef struct {
    int length;
    rubik_op_t *operations;
} rubik_sequence_t;

/*
 * Builds cube from 6 3x3 matrices of faces.
 * Original API order is U R F D L B
 */
rubik_cube_t rubik_make_cube(rubik_color_t mat[6][3][3]);
rubik_cube_t rubik_make_cube_from_char(char mat[6][3][3]);
/*
 * Builds a sequence out of an algorithm string.
 * Operation array is dynamic, and must be freed through rubik_destroy_sequence
 */
rubik_sequence_t rubik_make_sequence(char *s);
void rubik_destroy_sequence(rubik_sequence_t *t);

char* rubik_sequence_to_string(rubik_sequence_t *t);

/*
 * Convert cube into format compatible with solver API
 */
char* rubik_convert_facelet(rubik_cube_t c);

/*
 * Rotates an individual face by some direction, 
 * for rotating faces read from camera input
 */
rubik_face_t rubik_face_rotate(rubik_face_t face, rubik_dir_t dir);

/*
 * Parses sequence to create a solver friendly solution that takes away all top and bottom turns buy turning the cube to a solvable state
 */
rubik_sequence_t rubik_cube_remove_up_down(rubik_sequence_t *s);

/*
 * Mutate a sequence so that it performs the same operations but in a different rotation
 * 
 * @param bottom    After the cube rotation, this face becomes the new bottom.
 * ie. R_LEFT would rotate the entire cube along the left/up-plane, 
 * so that the left face is now on the bottom.
 * 
 * If bottom == NO_SIDE, do nothing.
 * 
 * Special cases:
 * R_UP means rotate twice along up/front-plane     (the same as doing R_FRONT twice)
 * R_DOWN means rotate twice along up/left-plane (the same as doing R_LEFT twice)
 * A rotation in the front/left-plane requires 3 separate rotations.
 */
void rubik_sequence_rotate(rubik_sequence_t *s, int idx, int len, rubik_side_t bottom);
#endif
