#include "reader.h" // for testing purposes, turns file input into contiguous memory space
#include "writer.h"
#include "points.h"
#include "filters.h"
#include <iostream>
#include <time.h>



int main(int argc, char** argv) {
    uint8_t skip_factor = 8;
    // image structure can be either sourced from a file for testing or a serial buffer for embedded applications
    struct Structures::HeadlessBitmap* image = read_file();
    if (image == nullptr) {
        std::cout << "File was not found.\n";
        return (1);
    }

    //point(image, 0xFF0000, 16, 16, 32);
    //point(image, 0x00FF00, 16 + 32, 16, 32);
    //point(image, 0x0000FF, 16 + 64, 16, 32);
    //point(image, 0xFFFFFF, 16 + 96, 16, 32);

    //Filters::gaussian(image, 2.0f);

    int32_t coordinates[] = { -3, -3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2 };

    // psuedo-random dots
    uint32_t col_val[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0x000000, 0xFFFFFF, 0xF0F000, 0xF005F0, 0xA51552};

    //image = scale(image, 32);
    //Filters::gaussian(image, 2.0f);

    std::cout << "Feature filtering...\n";

    // write to image, retain old_image for unmodified data
    struct Structures::HeadlessBitmap* old_image = copy(image);

    int max = 0;

    // _BlockSize should accomodate the estimated maximum stereoscopic deviation
    Structures::Grid pt_aggregate(old_image, 64);

    for (uint32_t y = 0; y < image->y; y++) {
        for (uint32_t x = 0; x < image->x; x++) {
            if (Filters::fast(old_image, x, y, coordinates, 1)) {
                point(image, 0x00FF00, x, y, 2);
                struct Structures::Point* point_ptr= (struct Structures::Point*)malloc(sizeof(struct Structures::Point));
                if (point_ptr == nullptr) return (1);
                point_ptr->x = x; point_ptr->y = y;
                pt_aggregate.register_point(old_image, point_ptr);
            }
            
        }
    }

    uint32_t* orb_kernel = Filters::gaussian_kernel(8, 16);

    


    

    write_bmp(image);
}