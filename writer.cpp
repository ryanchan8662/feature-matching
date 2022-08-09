#include "writer.h"

uint8_t write_file (struct HeadlessBitmap* data) {
    errno_t err;
    FILE* file_pointer;
    err = fopen_s(&file_pointer, "./test-images/output.bmp", "wb");
    if (file_pointer == nullptr) return (1);

    printf("Successfully written.\n");
}