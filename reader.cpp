#include "reader.h"

// reads BMP files ONLY!

struct ImageDataRGB* read_file() {


    // create heap space for image data
    struct ImageDataRGB* input_image = (struct ImageDataRGB*)malloc(sizeof(struct ImageDataRGB));
    if (input_image == nullptr) return(nullptr);

    errno_t err;
    FILE* file_pointer;
    err = fopen_s(&file_pointer, "test.bmp", "rb");
    if (file_pointer == nullptr) return (nullptr);

    fseek(file_pointer, 0, SEEK_END); // seek end of file
    uint32_t end_byte = ftell(file_pointer); // get file length
    fseek(file_pointer, 0, SEEK_SET); // reset to front


    // create heap space for file byte stream
    uint8_t* buffer = (uint8_t*)malloc(end_byte * sizeof(uint8_t));
    if (buffer == nullptr) return(nullptr);


    // read and conclude file
    fread(buffer, end_byte, 1, file_pointer);
    fclose(file_pointer);

    printf("Image data bytes 1, 2: %d\n", *((uint32_t*)buffer));
}