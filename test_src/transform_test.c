#include <stdio.h>

#include "transform.h"
#include "errors.h"

int no_image_to_grayscale_matrix() {
    struct grayscale_image *grayscale = to_grayscale_matrix(NULL);

    if (grayscale != NULL) {
        delete_grayscale(grayscale);

        return FAIL;
    }

    return SUCCESS;
}

int standard_to_grayscale_matrix(struct Image *image) {
    struct grayscale_image *grayscale = to_grayscale_matrix(image);

    if (grayscale == NULL)
        return FAIL;

    if (grayscale->height != image->image_header.height || grayscale->width != image->image_header.width) {
        delete_grayscale(grayscale);

        return FAIL;
    }

    for (int height = 0; height < grayscale->height; height++)
        for (int width = 0; width < grayscale->width; width++)
            if (*(grayscale->matrix + height * grayscale->width + width) != brightness(image->pixels + height * image->image_header.width + width)) {
                delete_grayscale(grayscale);

                return FAIL;
            }

    delete_grayscale(grayscale);

    return SUCCESS;
}

int to_grayscale_matrix_test(struct Image *image) {
    if (image == NULL)
        return FAIL;

    if (no_image_to_grayscale_matrix() != SUCCESS)
        return FAIL;

    if (standard_to_grayscale_matrix(image) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

int empty_image_from_grayscale_matrix(struct grayscale_image *grayscale) {
    if (from_grayscale_matrix(grayscale, NULL) != 0)
        return FAIL;

    return SUCCESS;
}    

int empty_grayscale_from_grayscale_matrix(struct Image *image) {
    if (from_grayscale_matrix(NULL, image) != 0)
        return FAIL;

    return SUCCESS;
}

int standard_from_grayscale_matrix(struct grayscale_image *grayscale, struct Image *image) {
    if (from_grayscale_matrix(grayscale, image) != 1)
        return FAIL;

    for (int height = 0; height < image->image_header.height; height++)
        for (int width = 0; width < image->image_header.width; width++)
            if (*(grayscale->matrix + height * grayscale->width + width) == BLACK) {
                if ((image->pixels + height * image->image_header.width + width)->red != 0)
                    return FAIL;
                
                if ((image->pixels + height * image->image_header.width + width)->green != 0)
                    return FAIL;

                if ((image->pixels + height * image->image_header.width + width)->blue != 0)
                    return FAIL;
            } else { 
                if ((image->pixels + height * image->image_header.width + width)->red != 255)
                    return FAIL;

                if ((image->pixels + height * image->image_header.width + width)->red != 255)
                    return FAIL;

                if ((image->pixels + height * image->image_header.width + width)->red != 255)
                    return FAIL;
            }
    
    return SUCCESS;
}

int from_grayscale_matrix_test(struct grayscale_image *grayscale, struct Image *image) {
    if (grayscale == NULL || image == NULL)
        return FAIL;
    
    if (empty_image_from_grayscale_matrix(grayscale) != SUCCESS)
        return FAIL;

    if (empty_grayscale_from_grayscale_matrix(image) != SUCCESS)
        return FAIL;

    if (standard_from_grayscale_matrix(grayscale, image) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

int out_of_bounds_treshold(struct grayscale_image *grayscale) {
    struct binary_image *binary = treshold(grayscale, -1);

    if (binary != NULL) {
        delete_binary(binary);

        return FAIL;
    }

    binary = treshold(grayscale, 256);

    if (binary != NULL) {
        delete_binary(binary);

        return FAIL;
    }

    return SUCCESS;
}     

int empty_grayscale_treshold() {
    struct binary_image *binary = treshold(NULL, 100);

    if (binary != NULL) {
        delete_binary(binary);

        return FAIL;
    }

    return SUCCESS;
}

int standard_treshold(struct grayscale_image *grayscale, int treshold_constant) {
    struct binary_image *binary = treshold(grayscale, treshold_constant);

    if (binary == NULL)
        return FAIL;

    if (grayscale->height != binary->height || grayscale->width != binary->width)
        return FAIL;

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++) {
            if (*(grayscale->matrix + height * grayscale->width + width) < treshold_constant) {
                if (*(binary->matrix + height * binary->width + width) != WHITE) {
                    delete_binary(binary);

                    return FAIL;
                }
            } else {
                if (*(binary->matrix + height * binary->width + width) != BLACK) {
                    delete_binary(binary);

                    return FAIL;
                }
            }
        }

    delete_binary(binary);

    return SUCCESS;
}

int treshold_test(struct grayscale_image *grayscale) {
    if (grayscale == NULL)
        return FAIL;

    if (empty_grayscale_treshold() != SUCCESS)
        return FAIL;

    if (out_of_bounds_treshold(grayscale) != SUCCESS)
        return FAIL;

    if (standard_treshold(grayscale, 100) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

int empty_binary_from_binary_to_grayscale() {
    struct grayscale_image *grayscale = from_binary_to_grayscale(NULL);

    if (grayscale != NULL) {
        delete_grayscale(grayscale);

        return FAIL;
    }

    return SUCCESS;
}

int standard_from_binary_to_grayscale_test(struct binary_image *binary) {
    struct grayscale_image *grayscale = from_binary_to_grayscale(binary);

    if (grayscale == NULL)
        return FAIL;

    if (grayscale->height != binary->height || grayscale->width != binary->width)
        return FAIL;

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++) {
            if (*(binary->matrix + height * grayscale->width + width) == BLACK) {
                if (*(grayscale->matrix + height * grayscale->width + width) != BLACK) {
                    delete_grayscale(grayscale);

                    return FAIL;
                } 
            } else {
                if (*(grayscale->matrix + height * grayscale->width + width) != WHITE) {
                    delete_grayscale(grayscale);

                    return FAIL;
                }
            }
        }

    delete_grayscale(grayscale);

    return SUCCESS;
}
                
int from_binary_to_grayscale_test(struct binary_image *binary) {
    if (binary == NULL)
        return FAIL;

    if (empty_binary_from_binary_to_grayscale() != SUCCESS)
        return FAIL;

    if (standard_from_binary_to_grayscale_test(binary) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

struct grayscale_image *minimal_to_grayscale(struct Image *image) {
    if (image == NULL)
        return NULL;

    struct grayscale_image *grayscale = malloc(sizeof(struct grayscale_image)); 

    if (grayscale == NULL)
        return NULL;
    
    grayscale->height = image->image_header.height;
    grayscale->width = image->image_header.width;

    grayscale->matrix = malloc(grayscale->width * grayscale->height * sizeof(unsigned char));

    if (grayscale->matrix == NULL)
        return NULL;

    for (int height = 0; height < grayscale->height; height++)
        for (int width = 0; width < grayscale->width; width++)
            *(grayscale->matrix + height * grayscale->width + width) = brightness(image->pixels + height * image->image_header.width + width);

    return grayscale;
}

struct binary_image *minimal_treshold(struct grayscale_image *grayscale, int treshold_constant) {
    if (grayscale == NULL)
        return NULL;

    if (treshold_constant < 0 || treshold_constant > 255)
        return NULL;

    struct binary_image *binary = malloc(sizeof(struct binary_image));

    if (binary == NULL)
        return NULL;

    binary->height = grayscale->height;
    binary->width = grayscale->width;

    binary->matrix = malloc(binary->height * binary->width * sizeof(enum binary_color));

    if (binary->matrix == NULL)
        return NULL;

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++)
            if (*(grayscale->matrix + height * grayscale->width + width) < treshold_constant)
                *(binary->matrix + height * binary->width + width) = WHITE;
            else
                *(binary->matrix + height * binary->width + width) = BLACK;

    return binary;
} 

int main() {
    struct Image *image = read_image_from_file("data/standard");

    struct grayscale_image *grayscale = minimal_to_grayscale(image);
    struct binary_image *binary = minimal_treshold(grayscale, 100);

    if (grayscale == NULL || binary == NULL)
        printf("Minimal implementations of transform functions failed\n");

    printf("to_grayscale_matrix() test -> ");
    evaluate(to_grayscale_matrix_test(image));

    printf("from_grayscale_matrix() test -> ");
    evaluate(from_grayscale_matrix_test(grayscale, image));

    printf("treshold() test -> ");
    evaluate(treshold_test(grayscale));

    printf("from_binary_to_grayscale() test -> ");
    evaluate(from_binary_to_grayscale_test(binary));

    printf("\n\n");

    delete_image(image);
    delete_grayscale(grayscale);
    delete_binary(binary);


    return 0;
}
