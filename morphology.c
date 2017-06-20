#include "colors.h"
#include "morphology.h"

enum kernel_state check_kernel(binary_image image, int width, int heigth, struct Kernel *kernel, int x, int y) {
    int kernel_state_count = 0;
    int index = 0;
    int leap = kernel->width / 2;

    for (int y_index = y - leap; y_index >= 0 && y_index <= y + leap && y_index < heigth; y_index++)
        for (int x_index = x - leap; x_index >= 0 && x_index <= x + leap && x_index < width; x_index++) {
            if (kernel->kernel[index] == image[index])
                kernel_state_count++;

            index++;
        }

    if (kernel_state_count == kernel->width * kernel->heigth)
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
    kernel->heigth = size;

    return kernel;
}

void delete_kernel(struct Kernel *kernel) {
    free(kernel);
}

// Using only odd square_size values
void fill_square(binary_image image, int width, int heigth,  int square_size, enum binary_color new_color, int x, int y) {
    for (int y_index = y - 1; y_index <= y + 1; y_index++)
        for (int x_index = x - 1; x_index <= x + 1; x_index++)
            image[y_index * width + x_index] = new_color;
}


/*
void binary_image erosion(binary_image image, struct Kernel *kernel) {
    binary_image *image_copy = malloc(heigth * width * sizeof(binary_image));

    for (int heigth_index = 0; heigth_index < heigth; heigth_index++)
        for (int width_index = 0; width_index < width; width_index++)
            if (image[heigth_index * width + width_index] == WHITE)
                if (check_kernel(image_copy, kernel, heigth_index, width_index) == FIT) {
                    for (int 

}
*/

void dilation(binary_image image, int heigth, int width, struct Kernel *kernel) {
    binary_image image_copy = malloc(heigth * width * sizeof(enum binary_color));
    int leap = kernel->width / 2;

    for (int heigth_index = 0; heigth_index < heigth; heigth_index++)
        for (int width_index = 0; width_index < width; width_index++) {
            if (image_copy[heigth_index * width + width_index] == WHITE)
                if (check_kernel(image_copy, width, heigth, kernel, width_index, heigth_index) != HIT)
                    for (int y_index = heigth_index - leap; y_index >= 0 && y_index < heigth && y_index <= heigth_index + leap; y_index++) 
                        for (int x_index = width_index - leap; x_index >= 0 && x_index < width && x_index <= width_index + leap; x_index++) 
                            image[y_index * width + x_index] = WHITE;
        }
}

/*

void opening(binary_image image, struct Kernel *kernel) {
    dilation(image, kernel);
    opening(image, kernel);
}

void closing(binary_image image, struct Kernel *kernel) {
    erosion(image, kernel);
    dilation(image, kernel);
}

*/
