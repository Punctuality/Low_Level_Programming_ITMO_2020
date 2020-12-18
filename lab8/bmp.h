//
// Created by Sergey Fedorov on 11/6/20.
//

#include <stdio.h>
#include <stdint.h>

#ifndef LOW_LEVEL_PROGRAMMING_ITMO_2020_BMP_H
#define LOW_LEVEL_PROGRAMMING_ITMO_2020_BMP_H

struct __attribute__((packed)) bmp_header {
    char     bfType[2];
    uint32_t bfSize;
    uint32_t bfReserved;
    uint32_t bfOffBits;

    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct bmp_pixel {
    uint8_t b, g, r;
};

struct bmp_image {
    struct bmp_header header;
    struct bmp_pixel* pixels;
};

enum bmp_read_result {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_BMP_FORMAT,
    READ_INVALID_BAD_PIXEL
};

enum bmp_write_result {
    WRITE_OK = 0,
    WRITE_BAD_HEADER,
    WRITE_BAD_BODY,
    WRITE_BAD_OFFSET
};

enum bmp_read_result bmp_image_read(struct bmp_image** bmp_image, FILE* file);
void free_bmp_image(struct bmp_image* image);

enum bmp_write_result bmp_image_write(const struct bmp_image* bmp_image, FILE * file);

#endif //LOW_LEVEL_PROGRAMMING_ITMO_2020_BMP_H
