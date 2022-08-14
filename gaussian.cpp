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
	int32_t accumulator = 0;
	printf("Kernel: \n");
	for (int32_t i = -range, counter = 0; i <= range; i++) {
		gaussian_kernel[counter] = 1 / (sqrt(2 * 3.141f * pow(_Sigma, 2)) * pow(2.718f, (pow(i, 2) / (2 * pow(_Sigma, 2)))));
		accumulator += 0xFF * gaussian_kernel[counter];
		printf("%.3f\n", gaussian_kernel[counter++]);
	}

	// horizontal pass ~~~~~~~~~~~~~~~~~~~~~~

	// create intermediate file structure
	struct HeadlessBitmap* h_data = (struct HeadlessBitmap*)malloc(sizeof(struct HeadlessBitmap));
	if (h_data == nullptr) return (nullptr);

	h_data->x = _Data->x - (uint32_t) range * 2; // pixels are removed from the left/right edges by the filter
	h_data->y = _Data->y; // no changes vertically
	h_data->pixel_width = _Data->pixel_width;

	// allocate padded and aligned space for data
	// row width * number of rows
	h_data->data = (uint8_t**)malloc(h_data->y * sizeof(uint8_t**));
	if (h_data->data == nullptr) return (nullptr);

	printf("Kernel size: %d, range: %d\n", kernel_size, range);
	printf("Before: %u x %u\n", _Data->x, _Data->y);
	printf("After: %u x %u\n", h_data->x, h_data->y);

	printf("Start blur sequence\n");
	// for each pixel, bounds of new image

	// for each row
	for (uint32_t y = 0; y < h_data->y; y++) {

		// allocate for current row, align to 4 bytes
		h_data->data[y] = (uint8_t*)((uintptr_t)malloc(h_data->x * h_data->pixel_width + 3) & ~(uintptr_t)0x3);
		if (h_data->data[y] == nullptr) return (nullptr);
		
		// for each pixel in each row
		for (uint32_t x = 0; x < h_data->x; x++) {
			
			// for each colour element
			for (uint8_t i = 0; i < h_data->pixel_width; i++) {

				uint32_t sum = 0;

				*(&h_data->data[y][x] + i) = *(&_Data->data[y][x + range] + i);

				// for each element in the filter
				//for (uint32_t j = 0; j < kernel_size; j++) {
					
				//sum += *(&_Data->data[y][x + range] + i);// * gaussian_kernel[j];

				//}

				//*(&h_data->data[y][x] + i) = (uint8_t)sum;

			}

		}
	}

	printf("End blur sequence\n");
	//free(_Data);
	// FREE EVERYTHING, ELSE (MEMORY LEAK)
	return (h_data);
	
}