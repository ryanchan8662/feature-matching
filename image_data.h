#ifndef IMAGE_DATA_STRUCTURES

#define IMAGE_DATA_STRUCTURES

struct ImageDataRGB {

    uint32_t file_size;
    uint32_t width, height;
    uint32_t fov, focal_length;

    uint8_t** pixel_data;

};

struct ImageDataBW {

    uint32_t file_size;
    uint32_t width, height;
    uint32_t fov, focal_length;

    uint8_t* pixel_data;

};

#endif