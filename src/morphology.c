#include "colors.h"
#include "morphology.h"

enum kernel_state _check_kernel(struct binary_image *image, struct Kernel *kernel, int x, int y) {
    int kernel_width_index = 0;
    int kernel_height_index = 0;

    int kernel_state_count = 0;
    int kernel_size = 0;

    for (int height = y - kernel->height / 2; height <= y + kernel->height / 2; height++) {
        int _height = height;

        if (height < 0)
            _height = 0;

        if (height >= image->height)
            _height = image->height - 1;

        for (int width = x - kernel->width / 2; width <= x + kernel->width / 2; width++) {
            int _width = width;

            if (width < 0)
                _width = 0;

            if (width >= image->width)
                _width = image->width - 1;

            if (*(kernel->kernel + kernel_height_index * kernel->width + kernel_width_index) == 1) {
                kernel_size++;

                if (*(image->matrix + _height * image->width + _width) == WHITE)
                    kernel_state_count++;
            }

            kernel_width_index++;
        }
        
        kernel_width_index = 0;
        kernel_height_index++;
    }

    if (kernel_state_count == kernel_size)
        return FIT;
    else if (kernel_state_count == 0)
        return OUT;
    else
        return HIT;

}

struct Kernel *square_kernel(int size) {
    struct Kernel *kernel = malloc(sizeof(struct Kernel));

    kernel->width = size;
    kernel->height = size;

    kernel->kernel = malloc(kernel->width * kernel->height * sizeof(char));

    for (int height = 0; height < kernel->height; height++)
        for (int width = 0; width < kernel->width; width++)
            *(kernel->kernel + height * kernel->width + width) = 1;

    return kernel;
}

void delete_kernel(struct Kernel *kernel) {
    free(kernel);
}

struct binary_image *_copy_binary(struct binary_image *image) {
    struct binary_image *copy = malloc(sizeof(struct binary_image));

    copy->height = image->height;
    copy->width = image->width;

    copy->matrix = malloc(copy->height * copy->width * sizeof(enum binary_color));

    for (int height = 0; height < copy->height; height++) {
        for (int width = 0; width < copy->width; width++) {
            *(copy->matrix + height * copy->width + width) = *(image->matrix + height * image->width + width);
        }
    }

    return copy;
}

void dilation(struct binary_image *image, struct Kernel *kernel) {
    struct binary_image *image_copy = _copy_binary(image);

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == BLACK) {
                if (_check_kernel(image_copy, kernel, width, height) == HIT) { 
                    *(image->matrix + height * image->width + width) = WHITE;
                }
            }

}

void erosion(struct binary_image *image, struct Kernel *kernel) {
    struct binary_image *image_copy = _copy_binary(image);

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == WHITE) {
                if (_check_kernel(image_copy, kernel, width, height) != FIT) {
                    *(image->matrix + height * image->width + width) = BLACK;
                }
            }
}

void opening(struct binary_image *image, struct Kernel *kernel) {
    dilation(image, kernel);
    erosion(image, kernel);
}

void closing(struct binary_image *image, struct Kernel *kernel) {
    erosion(image, kernel);
    dilation(image, kernel);
}
