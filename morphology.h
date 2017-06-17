#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "transform.h"
#include "colors.h"
#include "image.h"

struct Kernel {
    char *kernel;
    int width;
    int heigth;
}

enum kernel_state {FIT, HIT, OUT};

struct Kernel *squareKernel(int size);
void delete_kernel(struct Kernel kernel);

enum kernel_state check_kernel(binary_image image, struct Kernel *kernel, int x, int y);

void binary_image erosion(binary_image image, struct Kernel *kernel);
void binary_image dilation(binary_image image, struct Kernel *kernel);

void binary_image opening(binary_image image, struct Kernel *kernel);
void binary_image closing(binary_image image, strcut Kernel *kernel);

#endif
