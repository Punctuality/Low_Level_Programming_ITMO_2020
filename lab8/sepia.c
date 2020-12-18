//
// Created by Sergey Fedorov on 12/18/20.
//

#include "sepia.h"

extern void sepia_asm(float const *coefs, struct bmp_pixel* pixels, size_t size);

static unsigned char sat(uint64_t x) {
    if (x < 256) return x;
    return 255;
}

void naive_sepia_pixel(struct bmp_pixel* pixel) {
    static const float c[3][3] = {
            {C_1_1, C_1_2, C_1_3},
            {C_2_1, C_2_2, C_2_3},
            {C_3_1, C_3_2, C_3_3}
    };
    struct bmp_pixel const old = *pixel;

    pixel->r = sat(old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2]);
    pixel->g = sat(old.r * c[1][0] + old.g * c[1][1] + old.b * c[1][2]);
    pixel->b = sat(old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2]);
}

void naive_sepia(struct bmp_image* image) {
    struct bmp_pixel* pixel;
    for (int i = 0; i < image->header.biHeight * image->header.biWidth; i++) {
        pixel = &image->pixels[i];
        naive_sepia_pixel(pixel);
    }
}

void sse_sepia(struct bmp_image* image) {
    float cc[9] = {C_1_1, C_1_2, C_1_3,
                   C_2_1, C_2_2, C_2_3,
                   C_3_1, C_3_2, C_3_3};
//    float cc[9] = {.272f, .500f, .131f, .323f, .686f, .168f, .393f, .754f, .201f};
    size_t i;
    size_t full_size = image->header.biWidth * image->header.biHeight;
    size_t sse_num = full_size / 4;
    if (sse_num)
        sepia_asm(cc, image->pixels, sse_num);
    for (i = 4 * sse_num; i < full_size; ++i)
        naive_sepia_pixel(&image->pixels[i]);
}
