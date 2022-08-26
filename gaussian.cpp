#include "filters.h"
#include "writer.h"
#include "get_array.h"

using namespace Filters;

uint8_t Filters::gaussian (struct Structures::HeadlessBitmap* _Data, float _Sigma) {

	// generate convolutional kernel ~~~~~~~~~~~~~~~~~~~~~~~~

	// (_Sigma * 2.718f * 1.25f) = non-zero range of significant gaussian distribution
	// (_Sigma * 2.718f * 2.5f) + 1 = full range including centre of significant gaussian distribution
	float* gaussian_kernel = (float*)malloc(sizeof(float) * (size_t)(_Sigma * 2.718f * 2.5f) + 1);
	// check for good memory allocation or bad sigma value
	if (gaussian_kernel == nullptr || _Sigma <= 0.0f) return (1);

	// generate range of integer sample points
	int32_t range = (uint32_t)(2.718f * _Sigma + 1);
	int32_t kernel_size = range * 2 + 1;

	// generate gaussian kernel for image
	// https://en.wikipedia.org/wiki/Gaussian_blur
	float accumulator = 0.0f;
	for (int32_t i = -range, counter = 0; i <= range; i++) {
		gaussian_kernel[counter] = 1 / (sqrt(2 * 3.141f * pow(_Sigma, 2)) * pow(2.718f, (pow(i, 2) / (2 * pow(_Sigma, 2)))));
		accumulator += gaussian_kernel[counter++];
		//printf("%.3f\n", gaussian_kernel[counter++]);
	}

	
	// normalise for area of statistical distribution
	float normalise = 1.0f / accumulator;
	accumulator = 0.0f;
	for (int32_t i = 0; i < kernel_size; i++) {
		gaussian_kernel[i] *= normalise;
		accumulator += gaussian_kernel[i];
	}	

	// horizontal pass ~~~~~~~~~~~~~~~~~~~~~~

	// create intermediate file structure
	struct Structures::HeadlessBitmap* h_data = (struct Structures::HeadlessBitmap*)malloc(sizeof(struct Structures::HeadlessBitmap));
	if (h_data == nullptr) return (1);

	h_data->x = _Data->x - (uint32_t)range * 2; // pixels are removed from the left/right edges by the filter
	h_data->y = _Data->y; // no changes vertically
	h_data->pixel_width = _Data->pixel_width;

	// allocate padded and aligned space for data
	// row width * number of rows
	h_data->data = (uint8_t**)malloc(h_data->y * sizeof(uint8_t**));
	if (h_data->data == nullptr) return (1);

	printf("Kernel size: %d, range: %d\n", kernel_size, range);
	printf("Before: %u x %u\n", _Data->x, _Data->y);
	printf("After: %u x %u\n", h_data->x, h_data->y);

	// for each row
	for (uint32_t y = 0; y < h_data->y; y++) {

		// allocate for current row, align to 4 bytes
		h_data->data[y] = (uint8_t*)((uintptr_t)malloc(h_data->x * h_data->pixel_width + 3) & ~(uintptr_t)0x3);
		if (h_data->data[y] == nullptr) return (1);

		if (y == (h_data->y >> 1)) printf("Halfway there.\n");

		// for each pixel in each row
		for (uint32_t x = 0; x < h_data->x; x++) {

			// for each colour element
			for (uint8_t i = 0; i < h_data->pixel_width; i++) {

				float sum = 0.0f;



				// for each element in the filter
				for (uint32_t j = 0; j < kernel_size; j++) {

					sum += *(&_Data->data[y][(x + j) * _Data->pixel_width + i]) * gaussian_kernel[j];

				}

				*(&h_data->data[y][x * h_data->pixel_width + i]) = (uint8_t)sum;

			}

		}
	}

	// vertical pass ~~~~~~~~~~~~~~~~~~~~~~~~~

	struct Structures::HeadlessBitmap* v_data = (struct Structures::HeadlessBitmap*)malloc(sizeof(struct Structures::HeadlessBitmap));
	if (v_data == nullptr) return (1);

	v_data->x = h_data->x;
	v_data->y = h_data->y - (uint32_t)range * 2;
	v_data->pixel_width = h_data->pixel_width;

	// allocate padded and aligned space for data
	// row width * number of rows
	v_data->data = (uint8_t**)malloc(v_data->y * sizeof(uint8_t**));
	if (v_data->data == nullptr) return (1);

	printf("Kernel size: %d, range: %d\n", kernel_size, range);
	printf("Before: %u x %u\n", h_data->x, h_data->y);
	printf("After: %u x %u\n", v_data->x, v_data->y);

	// for each row
	for (uint32_t y = 0; y < v_data->y; y++) {

		// allocate for current row, align to 4 bytes
		v_data->data[y] = (uint8_t*)((uintptr_t)malloc(v_data->x * v_data->pixel_width + 3) & ~(uintptr_t)0x3);
		if (v_data->data[y] == nullptr) return (1);

		// for each pixel in each row
		for (uint32_t x = 0; x < v_data->x; x++) {

			// for each colour element
			for (uint8_t i = 0; i < v_data->pixel_width; i++) {

				float sum = 0.0f;



				// for each element in the filter
				for (uint32_t j = 0; j < kernel_size; j++) {

					sum += *(&h_data->data[y + j][x * h_data->pixel_width + i]) * gaussian_kernel[j];

				}

				*(&v_data->data[y][x * v_data->pixel_width + i]) = (uint8_t)sum;

			}

		}
	}

	// remove references to intermediate data structures
	
	for (uint32_t i = 0; i < h_data->y; i++) {
		free(h_data->data[i]);
	}

	free(h_data->data);
	free(h_data);

	for (uint32_t i = 0; i < _Data->y; i++) {
		free(_Data->data[i]);
	}

	free(_Data->data);

	_Data->x = v_data->x;
	_Data->y = v_data->y;
	_Data->data = v_data->data;

	//printf("Adjustment ratio: %.5f\n", ratioed);
	
	return (0);
}