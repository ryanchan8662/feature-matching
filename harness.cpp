#include "reader.h" // for testing purposes, turns file input into contiguous memory space
#include "writer.h"
#include "get_array.h" // simplified XY->N converter
#include <iostream>
#include <time.h>



int main(int argc, char** argv) {
    uint8_t skip_factor = 16;
    // image structure can be either sourced from a file for testing or a serial buffer for embedded applications
    struct HeadlessBitmap* image = read_file();
    if (image == nullptr) {
        std::cout << "File was not found.\n";
        return (1);
    }

    write_file(image);

    /*
    for (uint32_t y = 0; y < image->y; y += skip_factor) {
        for (uint32_t x = 0; x < image->x; x += skip_factor) {
            uint8_t* temp = to_pointer(image->data, x, y, image->x, image->y, image->pixel_width);
            if (temp == nullptr) std::cout << "Index not valid.";
            else {
                uint8_t average = (*temp + ++ * temp++ + *temp) / 3;
                //printf(" %3d ", average);
                if (average < 35) printf("   ");
                else if (average < 98) printf(": :");
                else if (average < 169) printf("XXX");
                else printf("###");
            }
        }
        printf("\n");
    }*/
}