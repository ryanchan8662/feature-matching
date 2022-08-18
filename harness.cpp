#include "reader.h" // for testing purposes, turns file input into contiguous memory space
#include "writer.h"
#include "get_array.h" // simplified XY->N converter
#include "filters.h"
#include <iostream>
#include <time.h>



int main(int argc, char** argv) {
    uint8_t skip_factor = 8;
    // image structure can be either sourced from a file for testing or a serial buffer for embedded applications
    struct HeadlessBitmap* image = read_file();
    if (image == nullptr) {
        std::cout << "File was not found.\n";
        return (1);
    }

    //point(image, 0xFF0000, 16, 16, 32);
    //point(image, 0x00FF00, 16 + 32, 16, 32);
    //point(image, 0x0000FF, 16 + 64, 16, 32);
    //point(image, 0xFFFFFF, 16 + 96, 16, 32);

    Filters::gaussian(image, 1.5f);

    //point(image, 0xFFFFFF, 16 + 96, 16, 1);

    uint32_t coordinates[] = { -3, -3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2 };

    uint8_t temp = Filters::fast(image, 512, 512, coordinates);
    
    write_bmp(image);
}