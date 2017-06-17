#include "colors.h"
#include "morphology.h"

struct Kernel *square_kernel(int size) {
    struct Kernel *kernel = malloc(size * size);

    for (int index = 0; index < size; index++)
        kernel->kernel[index] = 1;

    kernel->width = size;
    kernel->heigth = size;

    return kernel;
}

void delete_kernel(struct Kernel *kernel) {
    free(kernel);
}

void binary_image erosion(binary_image image, struct Kernel *kernel) {

}

void binary_image dilation(binary_image image, struct Kernel *kernel) {

}

void binary_image opening(binary_image image, struct Kernel *kernel) {
    dilation(image, kernel);
    opening(image, kernel);
}

void binary_image closing(binary_image, image, struct Kernel *kernel) {
    erosion(image, kernel);
    dilation(image, kernel);
}
