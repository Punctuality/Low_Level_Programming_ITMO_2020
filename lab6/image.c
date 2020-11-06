//
// Created by Sergey Fedorov on 11/6/20.
//

#include "image.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void free_image(struct image* image) {
    if (image != NULL) {
        free(image->data);
        free(image);
    }

}

int abs_to_int(double a){
    return abs((int) a);
}

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double sind(double angle) {
    double angleradians = angle * M_PI / 180.0;
    return sin(angleradians) * M_PI / 180.0;
}

double cosd(double angle) {
    double angleradians = angle * M_PI / 180.0;
    return cos(angleradians) * M_PI / 180.0;
}

struct positioned_pixel{
    double x, y;
    struct pixel pixel;
};

void image_rotate(struct image* image, double angle) {
    double center_x, center_y, alpha,
    min_x = DBL_MAX,min_y = DBL_MAX,
    max_x = -DBL_MAX, max_y = -DBL_MAX;

    uint32_t x, y, i, j, k, base_x, base_y, count;

    count = image->width * image->height;


    struct positioned_pixel* pixels;
    pixels = malloc(sizeof(struct positioned_pixel) * count);

    center_x = ((double) image->width) / 2;
    center_y = ((double) image->height) / 2;

    for (y = 0, i = 0; y < image->height; y++) {
        for (x = 0; x < image->width; x++, i++) {

            // Rotation matrix
            pixels[i].x = center_x + (x - center_x) * cos(angle) - (y - center_y) * sin(angle);
            pixels[i].y = center_y + (x - center_x) * sin(angle) + (y - center_y) * cos(angle);
            pixels[i].pixel = image->data[i];

            min_x = min(min_x, pixels[i].x);
            min_y = min(min_y, pixels[i].y);

            max_x = max(max_x, pixels[i].x);
            max_y = max(max_y, pixels[i].y);
        }
    }

    image->width = ceil(max_x - min_x + 1);
    image->height = ceil(max_y - min_y + 1);
    free(image->data);

    // calloc -> make background black
    image->data = calloc(image->width * image->height, sizeof(struct pixel));

    for (i = 0; i < count; ++i) {
        pixels[i].x -= min_x;
        pixels[i].y -= min_y;

        base_x = ceil(pixels[i].x);
        base_y = ceil(pixels[i].y);

        // Mix colours by deviation
        // Positions:
        //             top (1)
        //             ^^^^^
        // left(4) <- center (0) -> right(2)
        //             vvvvv
        //            bottom (3)

        for (k = 0; k < 5; ++k) {
            switch (k) {
                case 0:
                    x = base_x;
                    y = base_y;
                    alpha = (1 - abs_to_int(pixels[i].x - x)) * (1 - abs_to_int(pixels[i].y - y));
                    break;

                case 1:
                    x = base_x;
                    y = base_y - 1;
                    alpha = (1 - abs_to_int(x - pixels[i].x)) * (1 - min(pixels[i].y - y, 1));
                    break;

                case 2:
                    x = base_x + 1;
                    y = base_y;
                    alpha = (1 - min(x - pixels[i].x, 1)) * (1 - abs_to_int(y - pixels[i].y));
                    break;

                case 3:
                    x = base_x;
                    y = base_y + 1;
                    alpha = (1 - abs_to_int( x - pixels[i].x)) * (1 - min(y - pixels[i].y, 1));
                    break;

                case 4:
                    x = base_x - 1;
                    y = base_y;
                    alpha = (1 - min(pixels[i].x - x, 1)) * (1 - abs_to_int(y - pixels[i].y));
                    break;
            }

            if (x >= 0 && x < image->width && y >= 0 && y < image->height) {
                j = y * image->width + x;

                image->data[j].r += (pixels[i].pixel.r - image->data[j].r) * alpha;
                image->data[j].g += (pixels[i].pixel.g - image->data[j].g) * alpha;
                image->data[j].b += (pixels[i].pixel.b - image->data[j].b) * alpha;
            }
        }
    }

    free(pixels);
}
