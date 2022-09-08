#include "points.h"

using namespace Structures;

Grid::Grid (struct Structures::HeadlessBitmap* _Data, uint32_t _BlockSize):block_size(_BlockSize) {

	// initialise number of cells for future reference
	segments_x = (uint32_t)(_Data->x / _BlockSize) + 1;
	segments_y = (uint32_t)(_Data->y / _BlockSize) + 1;

	block_list = (struct Block**)malloc(segments_y * sizeof(struct Block*));
	if (block_list == nullptr) return;

	for (uint32_t y = 0; y < segments_y; y++) {
		block_list[y] = (struct Block*)malloc(segments_x * sizeof(struct Block));
		if (block_list[y] == nullptr) return;

		// initialise linked list with null references and zeroed
		for (uint32_t x = 0; x < segments_x; x++) {

			// allocate initial space for points in block
			block_list[y][x].point_list = (struct Point**)malloc(64 * sizeof(struct Point*));
			if (block_list[y][x].point_list == nullptr) {
				// SOMETHING HAS GONE WRONG!!!!!!11!!1!1!!!!11
				return;
			}
			block_list[y][x].alloc_space = 64;

			block_list[y][x].point_count = 0;


		}
	}

	return;

}


uint8_t Grid::register_point (struct Structures::HeadlessBitmap* _Data, struct Point* _Point) {
	// get current block by rounding, coordinates with division will directly translate to block indices
	struct Block* current_block = &block_list[_Point->y / block_size][_Point->x / block_size];

	// more space must be allocated, block allocation is currently full
	if (current_block->alloc_space == current_block->point_count) {

		struct Point** temp = current_block->point_list;

		// add space for current space / 2
		current_block->point_list = (struct Point**)realloc(current_block->point_list, current_block->alloc_space * sizeof(struct Point*) + ((current_block->alloc_space * sizeof(struct Point*)) >> 1));

		if (current_block->point_list == nullptr) {
			// no memory, reset to full array and do not add point
			current_block->point_list = temp;
			return (0xFF);
		}

		//free(temp);

		current_block->alloc_space += current_block->alloc_space >> 1;

	}

	current_block->point_list[current_block->point_count++] = _Point;

	current_block->point_count++;
	return (0);
}