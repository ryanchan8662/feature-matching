#include "get_array.h"

/// <summary>
/// Works with an [x][y] array, corresponds a 2-dimensional vector to a 1-dimensional array index pointer.
/// Returns the first element of the logical segment. Eg. channel R of an RGB representation
/// </summary>
/// <param name="input_array">Target array to retrieve data from</param>
/// <param name="x">First dimensional index</param>
/// <param name="y">Second dimensional index</param>
/// <param name="size_x">Horizontal width of array</param>
/// <param name="size_y">Vertical width of array</param>
/// <param name="period_size">Size of repeated element</param>
/// <returns>Pointer to first element of segment</returns>

uint8_t* to_pointer(uint8_t* input_array, uint32_t x, uint32_t y, uint32_t size_x, uint32_t size_y, uint32_t segment_size) {

	if (x >= size_x || y >= size_y) return (nullptr); // check for invalid requests


	return (input_array + ((y * size_x) + x)  * segment_size + 2 * y);

}