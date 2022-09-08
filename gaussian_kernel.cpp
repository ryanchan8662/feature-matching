#include "filters.h"

using namespace Filters;

// creates kernel of randomly generated point-pairs normally distributed
uint32_t* gaussian_kernel (uint32_t _Radius, uint32_t _Resolution) {

	// linear gaussian distribution: 1 / (sqrt(2 * 3.141f * pow(_Sigma, 2)) * pow(2.718f, (pow(i, 2) / (2 * pow(_Sigma, 2)))))

	// 2 points per resolution unit, 2 uint32_t per point
	uint32_t* r_val = (uint32_t*)malloc(_Resolution * 4 * sizeof(uint32_t));
	if (r_val == nullptr) return nullptr;

	for (uint32_t i = 0; i < _Resolution;) {
		// create 4 random points distributed normally, logically linked but structurally unlinked
	}

	return (nullptr); // incomplete


}