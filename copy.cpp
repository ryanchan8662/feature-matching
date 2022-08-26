#include "writer.h"


struct Structures::HeadlessBitmap* copy (struct Structures::HeadlessBitmap* _Data) {
	struct Structures::HeadlessBitmap* r_val = (struct Structures::HeadlessBitmap*)malloc(sizeof(struct Structures::HeadlessBitmap));
	if (r_val == nullptr) return (nullptr);

	r_val->x = _Data->x; r_val->y = _Data->y; r_val->pixel_width = _Data->pixel_width;

	r_val->data = (uint8_t**)malloc(r_val->y * sizeof(uint8_t*));
	if (r_val->data == nullptr) return (nullptr);

	for (uint32_t i = 0; i < r_val->y; i++) {
		r_val->data[i] = (uint8_t*)((uintptr_t)malloc(sizeof(uint8_t) * r_val->x * r_val->pixel_width + 3) & ~(uintptr_t)0x3);
		if (r_val->data[i] == nullptr) return (nullptr);

		uint32_t counter = 0;
		for (uint32_t j = 0; j < r_val->x * _Data->pixel_width; j++) {
			r_val->data[i][j] = _Data->data[i][j];
		}
	} return (r_val);
}