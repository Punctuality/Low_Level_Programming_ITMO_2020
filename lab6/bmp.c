//
// Created by Sergey Fedorov on 11/6/20.
//

#include "bmp.h"
#include "image.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

struct bmp_pixel {
    uint8_t b, g, r;
};

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

void bmp_to_image(struct bmp_image* bmp_image, struct image** new_image_p, int free_bmp) {
    struct image* new_image = malloc(sizeof(struct image));

    new_image->height = bmp_image->header.biHeight;
    new_image->width = bmp_image->header.biWidth;
    new_image->data = malloc(sizeof(struct pixel) * new_image->height * new_image->width);

    int32_t row, pos, index;

    for(row = 0; row < new_image->height; row++) {
        for(pos = 0; pos < new_image->width; pos++) {
            index = row * new_image->width + pos;
            struct pixel converted_pixel = {
                bmp_image->pixels[index].b,
                bmp_image->pixels[index].g,
                bmp_image->pixels[index].r
            };

            new_image->data[index] = converted_pixel;
        }
    }

    *new_image_p = new_image;

    if (free_bmp) {
        free_bmp_image(bmp_image);
    }
}

void image_to_bmp(struct image* image, struct bmp_image** new_bmp_image_p, int free_prev_image) {
    struct bmp_image* new_image = malloc(sizeof(struct bmp_image));

    new_image->header.biHeight = image->height;
    new_image->header.biWidth = image->width;

    new_image->header.bfType[0] = 'B';
    new_image->header.bfType[1] = 'M';
    new_image->header.bfOffBits = sizeof(struct bmp_header);

    new_image->header.biSize = 40;
    new_image->header.biPlanes = 1;
    new_image->header.biBitCount = 24;
    new_image->header.biCompression = 0;

    new_image->header.biSizeImage = new_image->header.biHeight *
            (new_image->header.biWidth * sizeof(struct bmp_pixel) + new_image->header.biWidth % 4);
    new_image->header.bfSize = new_image->header.bfOffBits + new_image->header.biSizeImage;

    new_image->pixels = malloc(sizeof(struct bmp_pixel) * new_image->header.biWidth * new_image->header.biHeight);

    int32_t row, pos, index;
    for(row = 0; row < new_image->header.biHeight; row++) {
        for(pos = 0; pos < new_image->header.biWidth; pos++) {
            index = row * new_image->header.biWidth + pos;

            struct bmp_pixel converted_pixel = {
                image->data[index].b,
                image->data[index].g,
                image->data[index].r
            };

            new_image->pixels[index] = converted_pixel;
        }
    }

    *new_bmp_image_p = new_image;

    if (free_prev_image) {
        free_image(image);
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
