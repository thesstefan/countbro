#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "image.h"
#include "colors.h"

#include <stdlib.h>

typedef unsigned char *grayscale_image;
typedef enum binary_color *binary_image;

grayscale_image to_grayscale_matrix(struct Image *image, double *treshold_ct);
grayscale_image from_binary_to_grayscale(binary_image binary, int size);
binary_image treshold(unsigned char *grayscale_matrix, int size, int treshold);
void from_grayscale_matrix(grayscale_image grayscale_matrix, struct Image *image);

#endif
