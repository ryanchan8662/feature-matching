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

    //point(image, 0xFF00FF, 256, 256, 16);
    image = Filters::gaussian(image, 32);
    
    write_bmp(image);
}