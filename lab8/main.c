#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <sys/resource.h>

#include "bmp.h"
#include "sepia.h"

#define INPUT_FILE "images/space.bmp"
#define OUTPUT_FILE "images/result.bmp"
#define TEST_ITER 10

long measure_method(struct bmp_image* img, void(*sepia)(struct bmp_image*)) {
    struct rusage r;
    struct timeval start;
    struct timeval end;

    getrusage(RUSAGE_SELF, &r);
    start = r.ru_utime;

    sepia(img);

    getrusage(RUSAGE_SELF, &r);
    end = r.ru_utime;

    return ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;
}

struct bmp_image* load_new_image(){
    struct bmp_image* image = malloc(sizeof(struct bmp_image));
    FILE* f = fopen(INPUT_FILE, "rb");

    bmp_image_read(&image, f);

    return image;
}

int main() {
    struct bmp_image* image;

    if (image == NULL) {
        fprintf(stderr, "Can't load image!\n");
        exit(EXIT_FAILURE);
    }

    double naive_res, sse_res;
    double results[2] = {0.0, 0.0};

    for (int i = 0; i < TEST_ITER; i++) {
        printf("TEST ITER %d:\n", i + 1);
        // NAIVE
        image = load_new_image();
        naive_res = measure_method(image, &naive_sepia) / 100000.0;
        free_bmp_image(image);
        printf("Time elapsed in seconds for NAIVE filter: %.2f\n", naive_res);
        // SSE
        image = load_new_image();
        sse_res = measure_method(image, &sse_sepia) / 100000.0;
        free_bmp_image(image);
        printf("Time elapsed in seconds for SSE filter: %.2f\n", sse_res);
        results[0] += naive_res;
        results[1] += sse_res;
    }

    results[0] /= TEST_ITER; results[1] /= TEST_ITER;
    printf("Medium: Naive = %.2f SSE = %.2f\n", results[0], results[1]);
    printf("SSE version is %.1f times faster!\n", results[0] / results[1]);

    image = load_new_image();

    sse_sepia(image);

    FILE* f_r = fopen(OUTPUT_FILE, "wb");
    bmp_image_write(image, f_r);
    free_bmp_image(image);

    return 0;
}
