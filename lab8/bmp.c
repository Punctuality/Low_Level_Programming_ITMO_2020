//
// Created by Sergey Fedorov on 11/6/20.
//

#include "bmp.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

enum bmp_read_result bmp_image_read(struct bmp_image** bmp_image, FILE * file) {
    struct bmp_image* image = malloc(sizeof(struct bmp_image));
    int32_t row, rowOffset;

    size_t read_count = fread(&(image->header), sizeof(struct bmp_header), 1, file);

    if (read_count < 1) {
        free(image);
        return READ_INVALID_HEADER;
    } else if (!(image->header.bfType[0] == 'B' && image->header.bfType[1] == 'M')) {
        free(image);
        return READ_INVALID_SIGNATURE;
    } else if (
        (image->header.biSizeImage != 0 && (image->header.bfSize != image->header.bfOffBits + image->header.biSizeImage))
        || (image->header.biCompression != 0)
        || (image->header.biPlanes != 1)) {
        free(image);
        return READ_INVALID_BMP_FORMAT;
    } else if (image->header.biBitCount != 24) {
        free(image);
        return READ_INVALID_BAD_PIXEL;
    }

    image->pixels = malloc(sizeof(struct bmp_pixel) * image->header.biWidth * image->header.biHeight);

    rowOffset = image->header.biWidth % 4;
    fseek(file, image->header.bfOffBits, SEEK_SET);
    for (row = image->header.biHeight - 1; row >= 0; --row) {
        read_count = fread(
            image->pixels + row * image->header.biWidth,
            sizeof(struct bmp_pixel),
            image->header.biWidth, file
        );

        if (read_count < image->header.biWidth) {
            free_bmp_image(image);
            return READ_INVALID_BITS;
        }

        if (fseek(file, rowOffset, SEEK_CUR) != 0) {
            free_bmp_image(image);
            return READ_INVALID_BITS;
        }
    }

    *bmp_image = image;
    return READ_OK;
}

void free_bmp_image(struct bmp_image* image) {
    if (image != NULL) {
        free(image->pixels);
        free(image);
    }
}

enum bmp_write_result bmp_image_write(const struct bmp_image* image, FILE* file) {
    static uint8_t offsetBuffer[] = { 0, 0, 0 };
    int32_t row, rowOffset;

    if (fwrite(&(image->header), sizeof(struct bmp_header), 1, file) == 0) {
        return WRITE_BAD_HEADER;
    }

    rowOffset = image->header.biWidth % 4;
    for (row = image->header.biHeight - 1; row >= 0; --row) {
        if (fwrite(image->pixels + row * image->header.biWidth,
                   sizeof(struct bmp_pixel), image->header.biWidth, file) < image->header.biWidth) {
            return WRITE_BAD_BODY;
        }

        if (fwrite(offsetBuffer, 1, rowOffset, file) < rowOffset) {
            return WRITE_BAD_OFFSET;
        }
    }

    return WRITE_OK;
}
