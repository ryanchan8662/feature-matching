#include "filters.h"
#include "writer.h"

using namespace Filters;

struct HeadlessBitmap* Filters::gaussian (struct HeadlessBitmap* _Data, float _Sigma) {
	// vertical pass

	// (_Sigma * 2.718f * 1.25f) = non-zero range of significant gaussian distribution
	// (_Sigma * 2.718f * 2.5f) + 1 = full range including centre of significant gaussian distribution
	float* gaussian_kernel = (float*)malloc(sizeof(float) * (size_t)(_Sigma * 2.718f * 2.5f) + 1);
	if (gaussian_kernel == nullptr) return (nullptr);

	uint32_t counter = 0;
	// generate gaussian distribution for image
	// https://en.wikipedia.org/wiki/Gaussian_blur
	for (int32_t i = -4; i <= 4; i++) {
		
		// generate gaussian distribution
		//gaussian_kernel[counter] = pow((1.0f / sqrt(2 * 3.141f * pow(_Sigma, 2))) * 2.718f,
			//-1 * pow(i, 2.0f) / (2 * pow(_Sigma, 2.0f)));
		//gaussian_kernel[counter] = (1.0f / sqrt(2 * 3.141f * pow(_Sigma, 2))) * 2.718f;
		gaussian_kernel[counter] = pow(0.542f, -0.125f);

		// issue: pow does not support negative exponents
		printf("%.3f\n", gaussian_kernel[counter++]);
	}
	printf("Gaussian transforms done. Sigma: %.3f\n", _Sigma);
	//printf("[%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f]\n", gaussian_kernel[0], gaussian_kernel[1], gaussian_kernel[2]
		//, gaussian_kernel[3], gaussian_kernel[4], gaussian_kernel[5], gaussian_kernel[6], gaussian_kernel[7], gaussian_kernel[8]);
}