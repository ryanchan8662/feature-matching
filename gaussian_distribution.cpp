
#include "filters.h"

using namespace Filters;


uint32_t* gaussian_distribution (uint32_t _Count, uint32_t _Radius) {
    /*
    * Let's say we have 16 equally sized bins to insert numbers into
    * And numbers must be chosen through a normal distribution
    * And the only generation is through a pseudo-random linear procedural generator
    * A threshold size of each bin can be dynamically adjusted using a normal distribution
    * The total size of the gaussian distribution can be calculated with the dismissible range found below
    * So rather than probability, the bins are organised by bin width, where the total length of the bin is 1
    * And bins are scaled to eliminate truncation error
    * A linear number transformation can be converted into a binned gaussian transformation
    *
    */
    // number of pairs * number of points per pair * number of uint32_t coordinate values per pair

    uint32_t* r_val = (uint32_t*)malloc(sizeof(uint32_t) * _Count * 2);

    float* bin_sizes = (float*)malloc(sizeof(float) * _Radius);
    float bin_sum = 0.0f;

    float sigma = (_Radius - 1) / 2.718f;

    for (uint32_t i = 0 ; i < _Radius; i++) {
        // for each bin/pixel in target distribution
        // generate float representing bin width
        bin_sizes[i] = 1 / (sqrt(2 * 3.141f * pow(sigma, 2)) * pow(2.718f, (pow(i, 2) / (2 * pow(sigma, 2)))));
        bin_sum += bin_sizes[i];
    }

    if (r_val == nullptr) {
        std::cout << "The penis monster has struck - out of memory" << std::endl;
        return (nullptr);
    }

    /*for (uint32_t i = 0; i < _Count * 2 * 2; i++) {
        // generate number with normal gaussian distribution, assign to current index
        r_val[i] = 0; // gaussian distribution placeholder
    }*/
    printf("Bin sum: %.2f\n", bin_sum);
    return (r_val);
}
