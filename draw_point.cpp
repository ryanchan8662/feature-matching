#include "writer.h"
#include "get_array.h"

void point(struct HeadlessBitmap* _Data, uint32_t _Rgb, uint32_t _LocationX, uint32_t _LocationY, uint16_t _PointSize) {

	for (int32_t x = -1 * (_PointSize >> 1); x < (_PointSize >> 1); x++) {
		for (int32_t y = -1 * (_PointSize >> 1); y < (_PointSize >> 1); y++) {

			//wipe RGB bits
			//*((uint8_t*)(&_Data->data[_LocationX + x][(_LocationY + y) * 3]) + 1) = 0xFF;
			*(uint32_t*)(&(_Data->data[_LocationY + y][(_LocationX + x) * 3])) &= ~0xFFFFFF;
			*(uint32_t*)(&_Data->data[_LocationY + y][(_LocationX + x) * 3]) = _Rgb;
		}
	}
}