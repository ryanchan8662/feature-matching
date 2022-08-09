#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef IMAGE_DATA
#define IMAGE_DATA
#include "image_data.h"
#endif

#ifndef GET_ARRAY
#define GET_ARRAY
uint8_t* to_pointer(uint8_t* _Array, uint32_t _TargetX, uint32_t _TargetY, uint32_t _SizeX, uint32_t _SizeY, uint32_t _ChunkSize);
#endif