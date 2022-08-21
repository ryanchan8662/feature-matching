#ifndef IMAGE_DATA_STRUCTURES

#define IMAGE_DATA_STRUCTURES

struct HeadlessBitmap {
	uint32_t x, y;
	uint8_t** data;
	uint8_t pixel_width;
};

#endif