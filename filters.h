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

#ifndef FILTERS
#define FILTERS

namespace Filters {

	uint8_t gaussian (struct HeadlessBitmap* _Data, float _Sigma);
	//struct HeadlessBitmap* sobel (struct HeadlessBitmap* _Data);
	uint8_t boxblur (struct HeadlessBitmap* _Data, uint32_t radius_Radius);
	//struct HeadlessBitmap* sharpen (struct HeadlessBitmap* _Data);
	//struct HeadlessBitmap* kovalevsky (struct HeadlessBitmap* _Data);
	//struct HeadlessBitmap* canny (struct HeadlessBitmap* _Data);

}

#endif