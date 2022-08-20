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

    Filters::gaussian(image, 2.0f);

    int32_t coordinates[] = { -3, -3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2 };

    // psuedo-random dots
    uint32_t col_val[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0x000000, 0xFFFFFF, 0xF0F000, 0xF005F0, 0xA51552};

    std::cout << "Feature filtering...\n";

    struct HeadlessBitmap* old_image = copy(image);

    int max = 0;

    for (uint32_t y = 0; y < image->y; y++) {
        for (uint32_t x = 0; x < image->x; x++) {
            if (Filters::fast(old_image, x, y, coordinates)) {
                point(image, 0xFF00FF, x, y, 2);
                if (x > max) max = x;
            }
            //point(image, 0xFF00FF, x, y, 2);
            
        }
    }    

    //point(image, 0x00FF00, 1024, 1024, 2);

    printf("X: %u, Y: %u, max: %d\n", image->x, image->y, max);
    write_bmp(image);
}