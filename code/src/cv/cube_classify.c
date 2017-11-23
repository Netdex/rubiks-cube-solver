#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "cv/cube_classify.h"

uint8_t* cube_classify_read_webcam(int *width, int *height, int *bpp){
    system("fswebcam --device /dev/video0 -q -r 640x480 --no-banner -S 30 temp.jpg");
    uint8_t* rgb_image = stbi_load("temp.jpg", width, height, bpp, 3);
    return rgb_image;
}

void cube_classify_face_image_argb(uint8_t *image, int bpp, int width, int height, rgb_t col_mat[3][3])
{
    // Regions to average
    // 3x3 is the face, 4 is x, y, w, h
    int regions[3][3][4] = {
        {{115, 69, 100, 100}, {268, 69, 100, 100}, {428, 69, 100, 100}},
        {{112, 216, 100, 100}, {268, 223, 100, 100}, {425, 230, 100, 100}},
        {{107, 368, 100, 100}, {261, 374, 100, 100}, {420, 377, 100, 100}}
    };

    assert(width == 640);
    assert(height == 480);
    assert(bpp == 3);

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            rgb_t ac = {0};

            for (int i = regions[y][x][1]; i < regions[y][x][1] + regions[y][x][3]; i++)
            {
                for (int j = regions[y][x][0]; j < regions[y][x][0] + regions[y][x][2]; j++)
                {
                    ac.r += ((float)image[(i * width + j) * 3]) / 255;
                    ac.g += ((float)image[(i * width + j) * 3 + 1]) / 255;
                    ac.b += ((float)image[(i * width + j) * 3 + 2]) / 255;
                }
            }
            ac.r /= regions[y][x][2] * regions[y][x][3];
            ac.g /= regions[y][x][2] * regions[y][x][3];
            ac.b /= regions[y][x][2] * regions[y][x][3];
            col_mat[y][x] = ac;
        }
    }
}

rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3])
{
    rubik_color_t cube_col[6][3][3];
    for(int f = 0; f < 6; f++){
        cube_col[f][1][1] = f;
    }
    for(int f = 0; f < 6; f++){
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                hsv_t col = rgb_to_hsv(colors[f][y][x]);
                printf("%.2f %.2f %.2f  ", col.hue, col.sat, col.val);
                if(x != 1 || y != 1){
                    float minDist = FLT_MAX;
                    int minFace = 0;
                    // find center facelet with minimum weighted rgb dist
                    for(int mf = 0; mf < 6; mf++){
                        //float dist = color_rgb_dist_sq(colors[f][y][x], colors[mf][1][1]);
                        float dist = color_rgb_to_hue_dist(colors[f][y][x], colors[mf][1][1]);
                        if(dist < minDist){
                            minDist = dist;
                            minFace = mf;
                        }
                    }
                    cube_col[f][y][x] = minFace;
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    rubik_cube_t cube = rubik_make_cube(cube_col);
    return cube;
}
