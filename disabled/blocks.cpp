#include "points.h"

using namespace Points;

class Points::Blocks {
private:
	uint32_t segments_x, segments_y;

	uint32_t block_size;

	struct Block** block_list;

public:
	Blocks (struct HeadlessBitmap* _Data, uint32_t _BlockSize) {

		segments_x = (uint32_t)(_Data->x / _BlockSize) + 1;
		segments_y = (uint32_t)(_Data->y / _BlockSize) + 1;

		block_size = _BlockSize;

		block_list = (struct Block**)malloc(segments_y * sizeof(struct Block*));
		if (block_list == nullptr) return;

		for (uint32_t y = 0; y < segments_y; y++) {
			block_list[y] = (struct Block*)malloc(segments_x * sizeof(struct Block));
			if (block_list[y] == nullptr) return;

			for (uint32_t x = 0; x < segments_x; x++) {
				block_list[y][x].point_count = 0;
			}
		}


	}
	uint8_t register_point (struct HeadlessBitmap* _Data, struct Point* _Point) {

	}

};