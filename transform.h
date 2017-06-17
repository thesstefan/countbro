#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "image.h"
#include "colors.h"

#include <stdlib.h>

typedef unsigned char *grayscale_image;
typedef enum binary_color *binary_image;

unsigned char *to_grayscale_matrix(struct Image *image);
struct Image* from_grayscale_matrix(unsigned char *grayscale_matrix);
enum binary_color *treshold(unsigned char *grayscale_matrix, int size, int treshold);

#endif
