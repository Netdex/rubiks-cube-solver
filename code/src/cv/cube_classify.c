#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "cv/cube_classify.h"
#include "cv/cluster.h"

uint8_t* cube_classify_read_webcam(int *width, int *height, int *bpp){
    system("fswebcam --device /dev/video1 -q -r 640x360 --no-banner -S 30 temp.jpg");
    uint8_t* rgb_image = stbi_load("temp.jpg", width, height, bpp, 3);
    return rgb_image;
}

void cube_classify_face_image_argb(uint8_t *image, int bpp, int width, int height, int x1, int y1, int x2, int y2, float pad, rgb_t col_mat[3][3])
{
    assert(x1 >= 0 && x1 < width && x2 >= 0 && x2 < height);
    assert(x1 < x2 && y1 < y2);
    assert(bpp == 3);
    assert(pad >= 0 && pad < 0.5);
    int dx = (x2 - x1) / 3;
    int dy = (y2 - y1) / 3;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            rgb_t ac = {0};

            for (int i = (int)(y1 + dy * y + dy * pad); i < (int)(y1 + dy * (y + 1) - dy * pad); i++)
            {
                for (int j = (int)(x1 + dx * x + dx * pad); j < (int)(x1 + dx * (x + 1) - dx * pad); j++)
                {
                    ac.r += ((float)image[(i * width + j) * 3]) / 255;
                    ac.g += ((float)image[(i * width + j) * 3 + 1]) / 255;
                    ac.b += ((float)image[(i * width + j) * 3 + 2]) / 255;
                }
            }
            ac.r /= (float)((dx - 2 * dx * pad) * (dy - 2 * dy * pad));
            ac.g /= (float)((dx - 2 * dx * pad) * (dy - 2 * dy * pad));
            ac.b /= (float)((dx - 2 * dx * pad) * (dy - 2 * dy * pad));
            col_mat[y][x] = ac;
        }
    }
}

rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3])
{
    rubik_color_t cube_col[6][3][3];
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                if(x == 1 && y == 1){
                    cube_col[f][y][x] = f;
                } else {
                    float minDist = FLT_MAX;
                    int minFace = 0;
                    // find center facelet with minimum weighted rgb dist
                    for(int mf = 0; mf < 6; mf++){
                        float dist = color_rgb_dist_sq(colors[f][y][x], colors[mf][1][1]);
                        if(dist < minDist){
                            minDist = dist;
                            minFace = mf;
                        }
                    }
                    cube_col[f][y][x] = minFace;
                }
            }
        }
    }
    rubik_cube_t cube = rubik_make_cube(cube_col);
    return cube;
}

rubik_cube_t cube_classify_cluster_from_colors(rgb_t colors[6][3][3])
{
    rgb_t *dataset = (rgb_t *)colors;

    LOG("k-means clustering...");
    // compute centroids
    rgb_t centroids[6];
    cluster_rgb_kmeans(6, 0.000001f, 10000, dataset, 6 * 3 * 3, centroids);
    // label dataset with computed centroids
    LOG("labelling...");
    int labels[6 * 3 * 3];
    cluster_rgb_label(6, dataset, 6 * 3 * 3, centroids, labels);

    LOG("building cube from labels...");
    // build cube using labels
    rubik_color_t cube_col[6][3][3];
    for (int f = 0; f < 6; f++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                // assign arbitrary color depending on label
                cube_col[f][y][x] = labels[f * 9 + y * 3 + x];
            }
        }
    }

    LOG("making cube from labels...");
    rubik_cube_t cube = rubik_make_cube(cube_col);
    return cube;
}