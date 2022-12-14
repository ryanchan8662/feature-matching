#include "writer.h"

// https://cse4k12.org/encoding/decoding_bmp.pdf
// Each row in the Pixel array is padded to a multiple of 4 bytes in size

uint8_t write_bmp (struct HeadlessBitmap* _Data) {
    
    FILE* file_pointer;
    file_pointer = fopen("../test-images/output.bmp", "wb");
    if (file_pointer == nullptr) return (1);
    
    uint16_t buffer_16 = 0x4D42; // fill with "BM" identifier
    fwrite(&buffer_16, sizeof(buffer_16), 1, file_pointer);
    
    uint32_t buffer_32 = 0x36 + ((_Data->x * _Data->pixel_width + 4) & ~0x3) * _Data->y; // byte size of file
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x0; // unused BMP header
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x36; // offset to start of pixel data
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x28; // number of bytes remaining in header
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);
    
    buffer_32 = _Data->x; // width of image in pixels
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = _Data->y; // height of image in pixels
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x1; // colour planes
    buffer_32 += (_Data->pixel_width * 8) << 16; // bits per pixel, shift so planes + pixel width = 4 bytes
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x0; // compression
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    //buffer_32 = data->x * data->y * data->pixel_width; // byte sum of pixel data
    buffer_32 = 0x0;
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x2E23; // x-res
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x2E23; // y-res
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x0; // number of colours in palette
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    buffer_32 = 0x0; // important colours
    fwrite(&buffer_32, sizeof(buffer_32), 1, file_pointer);

    for (uint32_t i = 0; i < _Data->y; i++) {
        fwrite(_Data->data[i], (_Data->x * _Data->pixel_width + 3) & ~0x3, 1, file_pointer);
    }

    fclose(file_pointer);
    // write image data

    //printf("Successfully written.\n");
    
    return (0);
}