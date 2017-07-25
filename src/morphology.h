#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "transform.h"
#include "colors.h"
#include "image.h"

struct Kernel {
    char *kernel;
    int width;
    int height;
};

enum kernel_state {FIT, HIT, OUT};

struct Kernel *square_kernel(int size);
void delete_kernel(struct Kernel *kernel);

void erosion(struct binary_image *image, struct Kernel *kernel);
void dilation(struct binary_image *image, struct Kernel *kernel);

void opening(struct binary_image *image, struct Kernel *kernel);
void closing(struct binary_image *image, struct Kernel *kernel);

#endif
