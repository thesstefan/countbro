#include "colors.h"
#include "morphology.h"

enum kernel_state _check_kernel(struct binary_image *image, struct Kernel *kernel, int x, int y) {
    int kernel_state_count = 0;

    int kernel_width_index = 0;
    int kernel_height_index = 0;

    for (int height = y - kernel->height / 2; height >= 0 && height < y + kernel->height / 2; height++) {
        for (int width = x - kernel->width / 2; width >= 0 && width < x + kernel->width / 2; width++) {
            if (*(kernel->kernel + kernel_height_index * kernel->width + kernel_width_index) == *(image->matrix + height * image->width + width))
               kernel_state_count++;

            kernel_width_index++;
        }
        
        kernel_width_index = 0;
        kernel_height_index++;
    }

    if (kernel_state_count == kernel->width * kernel->height)
        return FIT;
    else if (kernel_state_count == 0)
        return OUT;
    else
        return HIT;
}

struct Kernel *square_kernel(int size) {
    struct Kernel *kernel = malloc(size * size);

    for (int index = 0; index < size; index++)
        kernel->kernel[index] = 1;

    kernel->width = size;
    kernel->height = size;

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

void _dilate_here(struct binary_image *image, struct Kernel *kernel, int x, int y) {
   int kernel_height_index = 0;
   int kernel_width_index = 0;

   for (int height = y - kernel->height / 2; height >= 0 && height < y + kernel->height / 2; height++) {
      for (int width = x - kernel->width / 2; width >= 0 && width < x + kernel->width / 2; width++) {
          if (*(kernel->kernel + kernel_height_index * kernel->width + kernel_width_index) == 1)
              *(image->matrix + height * image->width + width) = BLACK;

          kernel_width_index++;
      }

      kernel_width_index = 0;
      kernel_height_index++;
   }
}

void _erode_here(struct binary_image *image, struct Kernel *kernel, int x, int y) {
    int kernel_height_index = 0;
    int kernel_width_index = 0;
          
    int fit = 0;

    for (int height = y - kernel->height / 2; height >= 0 && height < y + kernel->height / 2; height++) {
        for (int width = x - kernel->width / 2; width >= 0 && width < x + kernel->width / 2; width++) {
            if (*(kernel->kernel + kernel_height_index * kernel->width + kernel_width_index) == 1) {
                *(image->matrix + height * image->width + width) = WHITE;

                fit++;
            }

            kernel_width_index++;
        }

        kernel_width_index = 0;
        kernel_height_index++;
    }

    if (fit == kernel->height * kernel->width)
        *(image->matrix + y * image->width + x) = BLACK;
}

void dilation(struct binary_image *image, struct Kernel *kernel) {
    struct binary_image *image_copy = _copy_binary(image);

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == BLACK)
                if (_check_kernel(image_copy, kernel, width, height) == HIT) 
                    _dilate_here(image, kernel, width, height);
}

void erosion(struct binary_image *image, struct Kernel *kernel) {
    struct binary_image *image_copy = _copy_binary(image);

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == BLACK)
                if (_check_kernel(image_copy, kernel, width, height) != OUT)
                    _erode_here(image, kernel, width, height);
}

void opening(struct binary_image *image, struct Kernel *kernel) {
    dilation(image, kernel);
    opening(image, kernel);
}

void closing(struct binary_image *image, struct Kernel *kernel) {
    erosion(image, kernel);
    dilation(image, kernel);
}
