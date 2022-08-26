#ifndef IMAGE_DATA
#define IMAGE_DATA
#include "image_data.h"
#endif

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef MATH
#define MATH
#include <math.h>
#endif

#ifndef POINTS
#define POINTS

namespace Points {

	struct Point {
		uint32_t x, y;
		uint32_t descriptor;
		uint32_t score;
		struct Point* next;
	};

	struct Block {
		struct Point* front;
		uint32_t point_count;
	};

	class Blocks {
	private:
		uint32_t segments_x, segments_y;

		uint32_t block_size;

		struct Point** block_list;


	public:
		Blocks (struct HeadlessBitmap* _Data, uint32_t _BlockSize);
		uint8_t register_point (struct HeadlessBitmap* _Data, struct Point* _Point);

	};

}

#endif