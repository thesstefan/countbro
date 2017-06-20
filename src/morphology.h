#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "transform.h"
#include "colors.h"
#include "image.h"

struct Kernel {
    char *kernel;
    int width;
    int heigth;
};

enum kernel_state {FIT, HIT, OUT};

struct Kernel *square_kernel(int size);
void delete_kernel(struct Kernel *kernel);

enum kernel_state check_kernel(binary_image image, int width, int heigth, struct Kernel *kernel, int x, int y);

void fill_square(binary_image image, int width, int heigth, int square_size, enum binary_color new_color, int x, int y);

void erosion(binary_image image, struct Kernel *kernel);
void dilation(binary_image image, int heigth, int width, struct Kernel *kernel);

void opening(binary_image image, struct Kernel *kernel);
void closing(binary_image image, struct Kernel *kernel);

#endif
