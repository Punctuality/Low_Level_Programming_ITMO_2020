//
// Created by Sergey Fedorov on 11/6/20.
//

#include "bmp.h"

#include <stdio.h>

#define PATH_TO_IMAGE "images/lab6_test_big.bmp"
#define PATH_TO_IMAGE_RES "images/lab6_result.bmp"
#define ANGLE 45


int main() {
    struct bmp_image* b_image;
    FILE* test;
    test = fopen(PATH_TO_IMAGE, "rb");

    bmp_image_read(&b_image, test);

    struct image* image;

    bmp_to_image(b_image, &image, 0);

    printf("SIZE: %d %d\n", image->height, image->width);

    image_rotate(image, ANGLE * M_PI / 180.0);

    struct bmp_image* b_image_2;

    image_to_bmp(image, &b_image_2, 1);

    printf("TOP HEADER: %s %d %d %d\n",
           b_image->header.bfType, b_image->header.bfSize, b_image->header.bfReserved, b_image->header.bfOffBits);

    printf("TOP HEADER: %s %d %d %d\n",
           b_image_2->header.bfType, b_image_2->header.bfSize, b_image_2->header.bfReserved, b_image_2->header.bfOffBits);


    printf("BOTTOM HEADER: %d %d %d %d %d %d %d %d %d %d %d\n",
           b_image->header.biSize,
           b_image->header.biWidth,
           b_image->header.biHeight,
           b_image->header.biPlanes,
           b_image->header.biBitCount,
           b_image->header.biCompression,
           b_image->header.biSizeImage,
           b_image->header.biXPelsPerMeter,
           b_image->header.biYPelsPerMeter,
           b_image->header.biClrUsed,
           b_image->header.biClrImportant
    );

    printf("BOTTOM HEADER: %d %d %d %d %d %d %d %d %d %d %d\n",
           b_image_2->header.biSize,
           b_image_2->header.biWidth,
           b_image_2->header.biHeight,
           b_image_2->header.biPlanes,
           b_image_2->header.biBitCount,
           b_image_2->header.biCompression,
           b_image_2->header.biSizeImage,
           b_image_2->header.biXPelsPerMeter,
           b_image_2->header.biYPelsPerMeter,
           b_image_2->header.biClrUsed,
           b_image_2->header.biClrImportant
    );

    FILE* wtest;
    wtest = fopen(PATH_TO_IMAGE_RES, "wb");

    bmp_image_write(b_image_2, wtest);
}
