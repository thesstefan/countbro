#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "image.h"
#include "colors.h"

#include <stdlib.h>

typedef unsigned char **grayscale_matrix;
typedef enum binary_color **binary_color_matrix;

struct binary_image {
    int height;
    int width;

    binary_color_matrix matrix;
} __attribute__((__packed__));


struct grayscale_image {
    int height;
    int width;

    grayscale_matrix matrix;
} __attribute__((__packed__));

struct grayscale_image *to_grayscale_matrix(struct Image *image, double *treshold_ct);
struct grayscale_image *from_binary_to_grayscale(struct binary_image *binary);
struct binary_image *treshold(struct grayscale_image *grayscale, int treshold);
void from_grayscale_matrix(struct grayscale_image *grayscale_matrix, struct Image *image);

#endif
