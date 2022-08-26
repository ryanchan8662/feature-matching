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

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef FILE_WRITER
#define FILE_WRITER

uint8_t write_bmp(struct Structures::HeadlessBitmap* _Data);
void point(struct Structures::HeadlessBitmap* _Data, uint32_t _Rgb, uint32_t _LocationX, uint32_t _LocationY, uint16_t _PointSize);
struct Structures::HeadlessBitmap* copy (struct Structures::HeadlessBitmap* _Data);
struct Structures::HeadlessBitmap* scale (struct Structures::HeadlessBitmap* _Data, uint32_t _Scale);

#endif