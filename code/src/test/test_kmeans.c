#include "stdafx.h"
#include "cv/TinyPngOut.h"

void test_kmeans(){
    // Sample image data:
	//   [red    , green , blue]
	//   [magenta, yellow, cyan]
	const int width = 3;
	const int height = 2;
	uint8_t pixels[] = {
		0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	};
	
	// Initialize file and Tiny Png Output
	FILE *fout = fopen("demo-rgb.png", "wb");
	struct TinyPngOut pngout;
	if (fout == NULL || TinyPngOut_init(&pngout, fout, width, height) != TINYPNGOUT_OK)
		goto error;
	
	// Write image data
	if (TinyPngOut_write(&pngout, pixels, width * height) != TINYPNGOUT_OK)
		goto error;
	
	// Check for proper completion
	if (TinyPngOut_write(&pngout, NULL, 0) != TINYPNGOUT_DONE)
		goto error;
	fclose(fout);
	return;
error:
	fprintf(stderr, "Error\n");
	if (fout != NULL)
		fclose(fout);
}