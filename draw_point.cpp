#include "writer.h"
#include "get_array.h"

uint8_t point(struct HeadlessBitmap* _Data, uint32_t _Rgb, uint32_t _LocationX, uint32_t _LocationY, uint16_t _PointSize) {

	for (int32_t x = -1 * (_PointSize >> 1); x < (_PointSize >> 1); x++) {
		for (int32_t y = -1 * (_PointSize >> 1); y < (_PointSize >> 1); y++) {
			//printf("%d, %d\n", x, y);
			uint32_t* temp = (uint32_t*)to_pointer(_Data->data, _LocationX + x, _LocationY + y, _Data->x, _Data->y, _Data->pixel_width);

			//wipe RGB bits
			*temp &= ~0xFFFFFF;
			*temp |= _Rgb;
		}
	}

	return (0);
}