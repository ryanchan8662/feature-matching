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

#ifndef STRUCTURES
#define STRUCTURES

namespace Structures {
	struct Point {
		uint32_t x, y;
		uint32_t descriptor;
		uint32_t score;
	};

	struct Block {
		struct Point** point_list;
		uint32_t point_count; // STMIA pointer (empty stack)
		uint32_t alloc_space;
	};

	class Grid {
	private:
		uint32_t segments_x, segments_y;

		uint32_t block_size;

		struct Block** block_list;

	public:
		Grid (struct Structures::HeadlessBitmap* _Data, uint32_t _BlockSize);
		uint8_t register_point (struct Structures::HeadlessBitmap* _Data, struct Point* _Point);
	};
}

#endif