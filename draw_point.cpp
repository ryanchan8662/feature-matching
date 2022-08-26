#include "writer.h"
#include "get_array.h"

void point(struct Structures::HeadlessBitmap* _Data, uint32_t _Rgb, uint32_t _LocationX, uint32_t _LocationY, uint16_t _PointSize) {

	for (int32_t x = -1 * (_PointSize >> 1); x < (_PointSize >> 1); x++) {
		for (int32_t y = -1 * (_PointSize >> 1); y < (_PointSize >> 1); y++) {

			uint32_t x2 = (_LocationX + x);
			uint32_t y2 = _LocationY + y;

			// if point is within image boundaries
			if (!(x2 < 0 || x2 >= _Data->x || y2 < 0 || y2 >= _Data->y)) {

				// wipe current bits
				*(uint32_t*)(&(_Data->data[_LocationY + y][(_LocationX + x) * _Data->pixel_width])) &= ~0xFFFFFF;
				
				// set current bits
				*(uint32_t*)(&_Data->data[_LocationY + y][(_LocationX + x) * _Data->pixel_width]) |= _Rgb;
			}
			
		}
	}
}