#include <stdio.h>

#include "morphology.h"
#include "errors.h"

#define min(a,b) ((a) < (b)) ? (a) : (b)
#define max(a,b) ((a) > (b)) ? (a) : (b)
#define bound(a, b, c) (max(min(a, c), b))

enum kernel_state check_kernel_sample(struct binary_image *image, struct Kernel *kernel, int x, int y) {
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

struct Kernel *square_kernel_sample(int size) {
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


struct binary_image *copy_binary_sample(struct binary_image *image) {
    struct binary_image *copy = malloc(sizeof(struct binary_image));
    
    if (copy == NULL)
        return NULL;

    copy->height = image->height;
    copy->width = image->width;

    copy->matrix = malloc(copy->height * copy->width * sizeof(enum binary_color));

    if (copy->matrix == NULL) {
        delete_binary(copy);

        return NULL;
    }

    for (int height = 0; height < copy->height; height++) {
        for (int width = 0; width < copy->width; width++) {
            *(copy->matrix + height * copy->width + width) = *(image->matrix + height * image->width + width);
        }
    }

    return copy;
}


int out_of_bounds_square_kernel() {
    struct Kernel *kernel = square_kernel(-1);

    if (kernel != NULL) {
        delete_kernel(kernel);

        return FAIL;
    }

    kernel = square_kernel(KERNEL_MAX_SIZE + 1);

    if (kernel != NULL) {
        delete_kernel(kernel);

        return FAIL;
    }

    return SUCCESS;
}

int standard_square_kernel() {
    struct Kernel *kernel = square_kernel(20);

    if (kernel == NULL)
        return FAIL;

    if (kernel->width != 20 || kernel->height != 20) {
        delete_kernel(kernel);

        return FAIL;
    }

    for (int height = 0; height < kernel->height; height++)
        for (int width = 0; width < kernel->width; width++)
            if (*(kernel->kernel + height * kernel->width + width) != 1) {
                delete_kernel(kernel);

                return FAIL;
            }

    delete_kernel(kernel);

    return SUCCESS;
}

int square_kernel_test() {
    if (out_of_bounds_square_kernel() != SUCCESS)
        return FAIL;

    if (standard_square_kernel() != SUCCESS)
        return FAIL;

    return SUCCESS;
}

int empty_kernel_dilation(struct binary_image *image) {
    if (dilation(image, NULL) != 0)
        return FAIL;

    return SUCCESS;
}

int empty_image_dilation(struct Kernel *kernel) {
    if (dilation(NULL, kernel) != 0)
        return FAIL;

    return SUCCESS;
}

int standard_dilation(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return FAIL;

    if (dilation(image, kernel) != 1)
        return FAIL;

    struct binary_image *image_copy = copy_binary_sample(image);
    
    if (image_copy == NULL)
        return FAIL;

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == BLACK) 
                if (check_kernel_sample(image_copy, kernel, width, height) != HIT)
                    if (*(image->matrix + height * image->width + width) != WHITE) {
                        delete_binary(image_copy);

                        return FAIL;
                    }

    delete_binary(image_copy);

    return SUCCESS;
}

int dilation_test() {
    struct Image *image = read_image_from_file("/home/stefan/code/data/standard");
    struct grayscale_image *grayscale = to_grayscale_matrix(image);
    struct binary_image *binary = treshold(grayscale, 100);

    delete_image(image);
    delete_grayscale(grayscale);

    struct Kernel *kernel = square_kernel_sample(7);

    if (empty_kernel_dilation(binary) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (empty_image_dilation(kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (standard_dilation(binary, kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    delete_kernel(kernel);
    delete_binary(binary);

    return SUCCESS;
}

int empty_kernel_erosion(struct binary_image *image) {
    if (erosion(image, NULL) != 0)
        return FAIL;

    return SUCCESS;
}

int empty_image_erosion(struct Kernel *kernel) {
    if (erosion(NULL, kernel) != 0)
        return FAIL;

    return SUCCESS;
}

int standard_erosion(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return FAIL;

    if (erosion(image, kernel) != 1)
        return FAIL;

    struct binary_image *image_copy = copy_binary_sample(image);
    
    if (image_copy == NULL)
        return FAIL;

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image_copy->matrix + height * image->width + width) == WHITE) 
                if (check_kernel_sample(image_copy, kernel, width, height) != FIT)
                    if (*(image->matrix + height * image->width + width) != BLACK) {
                        delete_binary(image_copy);

                        return FAIL;
                    }

    delete_binary(image_copy);

    return SUCCESS;
}

int erosion_test() {
    struct Image *image = read_image_from_file("/home/stefan/code/data/standard");
    struct grayscale_image *grayscale = to_grayscale_matrix(image);
    struct binary_image *binary = treshold(grayscale, 100);

    delete_image(image);
    delete_grayscale(grayscale);

    struct Kernel *kernel = square_kernel_sample(7);

    if (empty_kernel_erosion(binary) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (empty_image_erosion(kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (standard_erosion(binary, kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    delete_kernel(kernel);
    delete_binary(binary);

    return SUCCESS;
}

int empty_image_opening(struct Kernel *kernel) {
    if (opening(NULL, kernel) != 0)
        return FAIL;

    return SUCCESS;
}

int empty_kernel_opening(struct binary_image *image) {
    if (opening(image, NULL) != 0)
        return FAIL;

    return SUCCESS;
}

int standard_opening(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return FAIL;

    if (opening(image, kernel) != 1)
        return FAIL;

    return SUCCESS;
}

int opening_test() {
    struct Image *image = read_image_from_file("/home/stefan/code/data/standard");
    struct grayscale_image *grayscale = to_grayscale_matrix(image);
    struct binary_image *binary = treshold(grayscale, 100);

    delete_image(image);
    delete_grayscale(grayscale);

    struct Kernel *kernel = square_kernel_sample(7);

    if (empty_kernel_opening(binary) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (empty_image_opening(kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (standard_opening(binary, kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    delete_kernel(kernel);
    delete_binary(binary);

    return SUCCESS;
}

int empty_image_closing(struct Kernel *kernel) {
    if (closing(NULL, kernel) != 0)
        return FAIL;

    return SUCCESS;
}

int empty_kernel_closing(struct binary_image *image) {
    if (closing(image, NULL) != 0)
        return FAIL;

    return SUCCESS;
}

int standard_closing(struct binary_image *image, struct Kernel *kernel) {
    if (image == NULL || kernel == NULL)
        return FAIL;

    if (closing(image, kernel) != 1)
        return FAIL;

    return SUCCESS;
}

int closing_test() {
    struct Image *image = read_image_from_file("/home/stefan/code/data/standard");
    struct grayscale_image *grayscale = to_grayscale_matrix(image);
    struct binary_image *binary = treshold(grayscale, 100);

    delete_image(image);
    delete_grayscale(grayscale);

    struct Kernel *kernel = square_kernel_sample(7);

    if (empty_kernel_closing(binary) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (empty_image_closing(kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    if (standard_closing(binary, kernel) != SUCCESS) {
        delete_kernel(kernel);
        delete_binary(binary);

        return FAIL;
    }

    delete_kernel(kernel);
    delete_binary(binary);

    return SUCCESS;
}

int main() {
    printf("square_kernel() test -> ");
    evaluate(square_kernel_test());

    printf("dilation() test -> ");
    evaluate(dilation_test());

    printf("erosion() test -> ");
    evaluate(erosion_test());

    printf("opening() test -> ");
    evaluate(opening_test());
    
    printf("closing() test -> ");
    evaluate(closing_test());

    printf("\n\n");

    return 0;
}    
