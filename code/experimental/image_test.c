#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

int main(void) {
    int width = 0, height = 0, bpp = 0;

    uint8_t* rgb_image = stbi_load("file.png", &width, &height, &bpp, 3);

    printf("loaded %dx%d image with %d bits per pixel", width, height, bpp);

    stbi_image_free(rgb_image);
    return 0;
}
