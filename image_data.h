#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef IMAGE_DATA_STRUCTURES

#define IMAGE_DATA_STRUCTURES

namespace Structures {
	struct HeadlessBitmap {
		uint32_t x, y;
		uint8_t** data;
		uint8_t pixel_width;
	};
}



#endif