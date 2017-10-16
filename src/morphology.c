#include "colors.h"
#include "morphology.h"

#define min(a,b) ((a) < (b)) ? (a) : (b)
#define max(a,b) ((a) > (b)) ? (a) : (b)
#define bound(a, b, c) (max(min(a, c), b))

enum kernel_state _check_kernel(struct binary_image *image, struct Kernel *kernel, int x, int y) {
    int kernel_width_index = 0;
    int kernel_height_index = 0;

    int kernel_state_count = 0;
    int kernel_size = 0;

    for (int height = y - kernel->height / 2; height <= y + kernel->height / 2; height++) {
        for (int width = x - kernel->width / 2; width <= x + kernel->width / 2; width++) {
            int safe_height = height;
            int safe_width  = width;

            safe_height = bound(height, 0, image->height - 1);
            safe_width = bound(width, 0, image->width - 1);

            if (*(kernel->kernel + kernel_height_index * kernel->width + kernel_width_index) == 1) {
                kernel_size++;

                if (*(image->matrix + safe_height * image->width + safe_width) == WHITE)
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
    if (size < 0 || size > KERNEL_MAX_SIZE)
        return NULL;

    struct Kernel *kernel = malloc(sizeof(struct Kernel));

    if (kernel == NULL)
        return NULL;

    kernel->width = size;
    kernel->height = size;

    kernel->kernel = malloc(kernel->width * kernel->height * sizeof(char));

    if (kernel->kernel == NULL) {
        delete_kernel(kernel);

        return NULL;
    }

    for (int height = 0; height < kernel->height; height++)
        for (int width = 0; width < kernel->width; width++)
            *(kernel->kernel + height * kernel->width + width) = 1;

    return kernel;
}

void delete_kernel(struct Kernel *kernel) {
    if (kernel != NULL)
        free(kernel->kernel);

    free(kernel);
}

struct binary_image *_copy_binary(struct binary_image *image) {
    if (image == NULL)
        return NULL;

    struct binary_image *copy = malloc(sizeof(struct binary_image));

    if (copy == NULL)
        return NULL;

    copy->height = image->height;
    copy->width = image->width;

    copy->matrix = malloc(copy->height * copy->width * sizeof(enum binary_color));

    if (copy->matrix == NULL)
        return NULL;

    for (int height = 0; height < copy->height; height++) {
        for (int width = 0; width < copy->width; width++) {
            *(copy->matrix + height * copy->width + width) = *(image->matrix + height * image->width + width);
        }
    }

    return copy;
}

int dilation(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return 0;

    struct binary_image *image_copy = _copy_binary(image);

    if (image_copy == NULL)
        return 0;

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == BLACK) {
                if (_check_kernel(image_copy, kernel, width, height) == HIT) { 
                    *(image->matrix + height * image->width + width) = WHITE;
                }
            }

    delete_binary(image_copy);
    
    return 1;
}

int erosion(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return 0;

    struct binary_image *image_copy = _copy_binary(image);

    if (image_copy == NULL)
        return 0;

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == WHITE) {
                if (_check_kernel(image_copy, kernel, width, height) != FIT) {
                    *(image->matrix + height * image->width + width) = BLACK;
                }
            }

    delete_binary(image_copy);

    return 1;
}

int opening(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return 0;

    if (dilation(image, kernel) != 1)
        return 0;

    if (erosion(image, kernel) != 1)
        return 0;

    return 1;
}

int closing(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return 0;

    if (erosion(image, kernel) != 1)
        return 0;

    if (dilation(image, kernel) != 1)
        return 0;

    return 1;
}
