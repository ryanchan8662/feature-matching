#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef IMAGE_DATA
#define IMAGE_DATA
#include "image_data.h"
#endif

#ifndef MATH
#define MATH
#include <math.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef FILTERS
#define FILTERS

namespace Filters {

	uint8_t gaussian (struct HeadlessBitmap* _Data, float _Sigma);
	
	uint8_t fast (struct HeadlessBitmap* _Data, uint32_t _X, uint32_t _Y, int32_t* _Seed, int8_t _Accuracy);

    uint32_t* gaussian_distribution (uint32_t _Count, uint32_t _Radius);

}

#endif