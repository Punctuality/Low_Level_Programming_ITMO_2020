//
// Created by Sergey Fedorov on 11/6/20.
//
#include <stdint.h>


#ifndef LOW_LEVEL_PROGRAMMING_ITMO_2020_IMAGE_H
#define LOW_LEVEL_PROGRAMMING_ITMO_2020_IMAGE_H

#define M_PI (3.14159265358979323846)

struct pixel {
    uint8_t b, g, r;
};

struct image {
    int32_t width, height;
    struct pixel* data;
};

void free_image(struct image* image);

void image_rotate(struct image* image, double angle);

// TODO
//void image_blur(struct image* image);
//void image_dilate(struct image* image);
//void image_erode(struct image* image);

#endif //LOW_LEVEL_PROGRAMMING_ITMO_2020_IMAGE_H
