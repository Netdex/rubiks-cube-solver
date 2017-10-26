#include "stdafx.h"
#include "cv/TinyPngOut.h"
#include "cv/graphics.h"
#include "cv/cluster.h"

void test_kmeans(){
    // create random dataset
    rgb_t dataset[512];
    for(int i = 0; i < 512; i++){
        dataset[i].r = randf();
        dataset[i].g = randf();
        dataset[i].b = randf();
    }
    
    // colors for classified clusters
    rgb_t class_col[] = {
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, 0.f, 1.f},
        {1.f, 1.f, 1.f},
        {1.f, .5f, 0.f},
        {1.f, 1.f, 0.f}
    };

    // compute centroids and labels
    rgb_t centroids[6];
    cluster_rgb_kmeans(6, 0.0001, 1000, dataset, 512, centroids);
    int labels[512];
    cluster_rgb_label(6, dataset, 512, centroids, labels);

    // draw output to file
    const int width = 1024, height = 1024;
    LOG("create image context");
    image_t image = gfx_create_image(width, height);
    
    for(int i = 0; i < 512; i++){
        int proj_x = (int)(dataset[i].r * width / 4 + width * dataset[i].b * 1.414f * 0.5f);
        int proj_y = (int)(dataset[i].g * height / 4 + height * dataset[i].b * 1.414f * 0.5f);
        int sz = (int)(dataset[i].b * 5) + 5;

        gfx_rect(image, 
            proj_x - sz/2, 
            proj_y - sz/2, 
            sz, sz, 
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