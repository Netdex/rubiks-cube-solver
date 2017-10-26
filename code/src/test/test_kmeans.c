#include "stdafx.h"
#include "cv/TinyPngOut.h"
#include "cv/graphics.h"
#include "cv/cluster.h"

void test_kmeans(){
    rgb_t dataset[512];
    for(int i = 0; i < 512; i++){
        dataset[i].r = randf();
        dataset[i].g = randf();
        dataset[i].b = randf();
    }

    rgb_t class_col[] = {
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, 0.f, 1.f},
        {1.f, 1.f, 1.f},
        {1.f, .5f, 0.f},
        {1.f, 1.f, 0.f}
    };

    rgb_t centroids[6];
    cluster_rgb_kmeans(6, 0.0001, 1000, dataset, 512, centroids);
    int labels[512];
    cluster_rgb_label(6, dataset, 512, centroids, labels);

    const int width = 512, height = 512;
    LOG("create image context");
    image_t image = gfx_create_image(width, height);
    
    for(int i = 0; i < 512; i++){
        gfx_rect(image, 
            (int)(dataset[i].r * 512) - 2, 
            (int)(dataset[i].g * 512) - 2, 
            5,5, 
            (rgb_t){
                dataset[i].b,
                dataset[i].b,
                dataset[i].b
        });
        gfx_rect(image, 
            (int)(dataset[i].r * 512) - 1, 
            (int)(dataset[i].g * 512) - 1, 
            3, 3, 
            class_col[labels[i]]
        );
    }

    uint8_t *pixels = malloc(3 * width * height);
    gfx_convert_buf(image, pixels);
    
	FILE *fout = fopen("output.png", "wb");
	struct TinyPngOut pngout;
	if (fout == NULL || TinyPngOut_init(&pngout, fout, width, height) != TINYPNGOUT_OK)
		goto error;
	if (TinyPngOut_write(&pngout, pixels, width * height) != TINYPNGOUT_OK)
		goto error;
	if (TinyPngOut_write(&pngout, NULL, 0) != TINYPNGOUT_DONE)
		goto error;
    fclose(fout);
    free(pixels);
	return;
error:
	if (fout != NULL)
		fclose(fout);
}