#include "stdafx.h"

#include "cv/cube_classify.h"
#include "cv/cluster.h"

rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3]){
    rgb_t *dataset = (rgb_t*) colors;

    // compute centroids
    rgb_t centroids[6];
    cluster_rgb_kmeans(6, 0.0001, 1000, dataset, 6 * 3 * 3, centroids);
    // label dataset with computed centroids
    int labels[6 * 3 * 3];
    cluster_rgb_label(6, dataset, 512, centroids, labels);

    // build cube using labels
    rubik_color_t cube_col[6][3][3];
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                // assign arbitrary color depending on label
                cube_col[f][y][x] = (rubik_color_t)(labels[f * 9 + y * 3 + x]);
            }
        }
    }
    rubik_cube_t cube = rubik_make_cube(cube_col);
    return cube;
}