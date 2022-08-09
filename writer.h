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

#ifndef FILE_WRITER
#define FILE_WRITER
uint8_t write_file(struct HeadlessBitmap* _Data);
#endif