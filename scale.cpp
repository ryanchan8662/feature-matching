#include "writer.h"


struct Structures::HeadlessBitmap* scale (struct Structures::HeadlessBitmap* _Data, uint32_t _Scale) {
	struct Structures::HeadlessBitmap* r_val = (struct Structures::HeadlessBitmap*)malloc(sizeof(struct Structures::HeadlessBitmap));
	if (r_val == nullptr) return (nullptr);

	r_val->x = _Data->x / _Scale; r_val->y = _Data->y / _Scale; r_val->pixel_width = _Data->pixel_width;

	r_val->data = (uint8_t**)malloc(r_val->y * sizeof(uint8_t*));
	if (r_val->data == nullptr) return (nullptr);

	for (uint32_t i = 0; i < r_val->y; i++) {
		r_val->data[i] = (uint8_t*)((uintptr_t)malloc(sizeof(uint8_t) * r_val->x * r_val->pixel_width + 3) & ~(uintptr_t)0x3);
		if (r_val->data[i] == nullptr) return (nullptr);

		uint32_t counter = 0;
		for (uint32_t j = 0; j < r_val->x; j++) {

			for (uint32_t rgb = 0; rgb < r_val->pixel_width; rgb++) {

				r_val->data[i][j * r_val->pixel_width + rgb] = _Data->data[i * _Scale][j * _Data->pixel_width * _Scale + rgb];

			}

		}
	} return (r_val);
}