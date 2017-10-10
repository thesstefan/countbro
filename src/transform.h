#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "image.h"
#include "colors.h"

#include <stdlib.h>

struct binary_image {
    int height;
    int width;

    enum binary_color *matrix;
} __attribute__((__packed__));


struct grayscale_image {
    int height;
    int width;

    unsigned char *matrix;
} __attribute__((__packed__));

unsigned char brightness(struct PIXEL *pixel);
struct grayscale_image *to_grayscale_matrix(struct Image *image);
struct grayscale_image *from_binary_to_grayscale(struct binary_image *binary);
struct binary_image *treshold(struct grayscale_image *grayscale, int treshold_constant);
int from_grayscale_matrix(struct grayscale_image *grayscale_matrix, struct Image *image);
void delete_grayscale(struct grayscale_image *grayscale);
void delete_binary(struct binary_image *binary);

#endif
