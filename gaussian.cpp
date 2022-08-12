#include "filters.h"
#include "writer.h"
#include "get_array.h"

using namespace Filters;

struct HeadlessBitmap* Filters::gaussian (struct HeadlessBitmap* _Data, float _Sigma) {

	// generate convolutional kernel ~~~~~~~~~~~~~~~~~~~~~~~~

	// (_Sigma * 2.718f * 1.25f) = non-zero range of significant gaussian distribution
	// (_Sigma * 2.718f * 2.5f) + 1 = full range including centre of significant gaussian distribution
	float* gaussian_kernel = (float*)malloc(sizeof(float) * (size_t)(_Sigma * 2.718f * 2.5f) + 1);
	// check for good memory allocation or bad sigma value
	if (gaussian_kernel == nullptr || _Sigma <= 0.0f) return (nullptr);

	// generate range of integer sample points
	int32_t range = (uint32_t)(2.718f * _Sigma + 1);
	int32_t kernel_size = range * 2 + 1;
	
		// generate gaussian kernel for image
		// https://en.wikipedia.org/wiki/Gaussian_blur
	for (int32_t i = -range, counter = 0; i <= range; i++) 
		gaussian_kernel[counter++] = 1 / (sqrt(2 * 3.141f * pow(_Sigma, 2)) * pow(2.718f, (pow(i, 2) / (2 * pow(_Sigma, 2)))));

	// work stuff to do:
	// actual pokemon robot documentation

	// horizontal pass ~~~~~~~~~~~~~~~~~~~~~~

	// create intermediate file structure
	struct HeadlessBitmap* horizontal = (struct HeadlessBitmap*)malloc(sizeof(struct HeadlessBitmap));
	if (horizontal == nullptr) return (nullptr);

	horizontal->x = _Data->x - (uint32_t) range * 2; // pixels are removed from the left/right edges by the filter
	// MAY BE A SITE OF FUTURE BUGS, REVISE LATER - SHOULD BE "(uint32_t) range * 2" ~~~~~~~~~~~~~~~~~~~
	horizontal->y = _Data->y; // no changes vertically
	horizontal->pixel_width = _Data->pixel_width;

	// allocate padded and aligned space for data
	// row width * number of rows
	horizontal->data = (uint8_t*)((uintptr_t)malloc((horizontal->x * horizontal->pixel_width + 4) * horizontal->y) & ~(uintptr_t)0x3);

	printf("Kernel size: %d, range: %d\n", kernel_size, range);
	printf("Before: %u x %u\n", _Data->x, _Data->y);
	printf("After: %u x %u\n", horizontal->x, horizontal->y);

	printf("Start blur sequence\n");
	// for each pixel, bounds of new image
	for (uint32_t x = 0; x < horizontal->x; x++) {
		for (uint32_t y = 0; y < horizontal->y; y++) {

			// get pointer to first channel of pixel
			// offset new_ptr x by size of filter
			uint8_t* new_ptr = to_pointer(horizontal->data, x, y, horizontal->x, horizontal->y, horizontal->pixel_width);
			uint8_t* old_ptr = to_pointer(_Data->data, x + (uint32_t)range, y, _Data->x, _Data->y, _Data->pixel_width);

			// and for each pixel's individual channels
			for (uint8_t z = 0; z < horizontal->pixel_width; z++) {

				// for each neighbour pixel weighted on kernel, add to pixel sum
				uint32_t temp = 0;
				for (int32_t a = -range; a <= range; a++) {
					// *(new_ptr + z) = offset by channel number from pixel address origin = channel of a pixel
					// *(old_ptr + z + a) = offset by channel, set back/forwards number of pixels shifted
					temp += (*(old_ptr + z + (a * _Data->pixel_width))) * gaussian_kernel[a];
					//*(new_ptr + z) += (* (old_ptr + z + (a * _Data->pixel_width))) * gaussian_kernel[a];
				}
				*(new_ptr + z) = (uint8_t)(temp > 255 ? (0) : temp);
			}
		}
	}

	printf("End blur sequence\n");

	return (horizontal);
	
}