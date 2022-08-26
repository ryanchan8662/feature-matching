#include "reader.h"


// reads BMP files ONLY!

uint32_t decode_int(uint8_t* buffer, uint32_t start_point) {


    uint32_t return_value = 0; // accumulator
    uint8_t shift_counter = 0; // number of shifts done to current buffer


    while (shift_counter <= 3) {
        // read current byte, increment byte counter
        // shift by number of bits per byte, multiply by "units" accumulated
        return_value += buffer[start_point++] << (shift_counter++ * 8);
    }

    return (return_value);
}

struct Structures::HeadlessBitmap* read_file() {

    errno_t err;
    FILE* file_pointer;
    err = fopen_s(&file_pointer, "./test-images/test4.bmp", "rb");
    if (file_pointer == nullptr) return (nullptr);
    

    uint32_t* file_size = (uint32_t*)malloc(sizeof(uint32_t));
    uint32_t* header_size = (uint32_t*)malloc(sizeof(uint32_t));
    if (file_size == nullptr || header_size == nullptr) return (nullptr);

    // get total file size
    fseek(file_pointer, 0x02, SEEK_SET);
    fread(file_size, 4, 1, file_pointer);

    // get total header size (offset until data)
    fseek(file_pointer, 0x0A, SEEK_SET);
    fread(header_size, 4, 1, file_pointer);

    // create return value object
    struct Structures::HeadlessBitmap* return_value = (Structures::HeadlessBitmap*)malloc(sizeof(Structures::HeadlessBitmap));
    if (return_value == nullptr) return (nullptr);

    // get x, y sizes
    fseek(file_pointer, 0x12, SEEK_SET);
    fread(&(return_value->x), 4, 1, file_pointer);

    fseek(file_pointer, 0x16, SEEK_SET);
    fread(&(return_value->y), 4, 1, file_pointer);

    return_value->pixel_width = 3;

    // since BMP formats pad each row to 4 bytes, allocate space aligned to 4 bytes
    // to get end of current row, align pointer to double words


    // initialise double pointer to store individual rows 
    return_value->data = (uint8_t**)malloc(sizeof(uint8_t*) * return_value->y);
    if (return_value->data == nullptr) return (nullptr);

    for (uint32_t i = 0; i < return_value->y; i++) {
        // create padded and aligned pointer
        return_value->data[i] = (uint8_t*)((uintptr_t)malloc(sizeof(uint8_t) * return_value->x * return_value->pixel_width + 3) & ~(uintptr_t)0x3);
        fseek(file_pointer, *header_size + ((((return_value->x * return_value->pixel_width + 3) & ~0x3) * i)), SEEK_SET);
        fread(return_value->data[i], (return_value->x * return_value->pixel_width + 3) & ~0x3, 1, file_pointer);
    }

    fclose(file_pointer);

    printf("Read %u lines\n", return_value->y);

    // get pixel data

    printf("Total size: %d, header size: %d, X: %d, Y: %d\n", *file_size, *header_size, return_value->x, return_value->y);
    
    return (return_value);
}