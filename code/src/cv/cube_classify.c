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

void cube_classify_face_image_argb(uint8_t *image, int bpp, int width, int height, int x1, int y1, int x2, int y2, rgb_t col_mat[3][3])
{
    assert(x1 >= 0 && x1 < width && x2 >= 0 && x2 < height);
    assert(x1 < x2 && y1 < y2);
    assert(bpp == 3);

    int dx = (x2 - x1) / 3;
    int dy = (y2 - y1) / 3;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            rgb_t ac = {0};

            for (int i = y1; i < y1 + dy * (y + 1); i++)
            {
                for (int j = x1; j < x1 + dx * (x + 1); j++)
                {
                    ac.r += ((float)image[(i * width + j) * 3]) / 255;
                    ac.g += ((float)image[(i * width + j) * 3 + 1]) / 255;
                    ac.b += ((float)image[(i * width + j) * 3 + 2]) / 255;
                }
            }
            ac.r /= (float)(dx * dy);
            ac.g /= (float)(dx * dy);
            ac.b /= (float)(dx * dy);
            col_mat[y][x] = ac;
        }
    }
}

rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3])
{
    rgb_t *dataset = (rgb_t *)colors;

    // compute centroids
    rgb_t centroids[6];
    cluster_rgb_kmeans(6, 0.0001, 1000, dataset, 6 * 3 * 3, centroids);
    // label dataset with computed centroids
    int labels[6 * 3 * 3];
    cluster_rgb_label(6, dataset, 512, centroids, labels);

    // build cube using labels
    rubik_color_t cube_col[6][3][3];
    for (int f = 0; f < 6; f++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                // assign arbitrary color depending on label
                cube_col[f][y][x] = (rubik_color_t)(labels[f * 9 + y * 3 + x]);
            }
        }
    }
    rubik_cube_t cube = rubik_make_cube(cube_col);
    return cube;
}