#include "transform.h"

unsigned char brightness(struct PIXEL *pixel) {
    return (0.9 * pixel->red + 0.5 * pixel->green + 0.5 * pixel->blue);
}

struct grayscale_image *to_grayscale_matrix(struct Image *image) {
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

int from_grayscale_matrix(struct grayscale_image *grayscale, struct Image *image) {
    if (grayscale == NULL)
        return 0;

    if (image == NULL)
        return 0;

    for (int height = 0; height < image->image_header.height; height++) {
        for (int width = 0; width < image->image_header.width; width++) {
            if (*(grayscale->matrix + height * grayscale->width + width) == BLACK) {
                (image->pixels + height * image->image_header.width + width)->red = 0;
                (image->pixels + height * image->image_header.width + width)->green = 0;
                (image->pixels + height * image->image_header.width + width)->blue = 0;
            } else {
                (image->pixels + height * image->image_header.width + width)->red = 255;
                (image->pixels + height * image->image_header.width + width)->green = 255;
                (image->pixels + height * image->image_header.width + width)->blue = 255;
            }
        }
    }

    return 1;
}

struct binary_image *treshold(struct grayscale_image *grayscale, int treshold_constant) {
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

struct grayscale_image *from_binary_to_grayscale(struct binary_image *binary) {
    if (binary == NULL)
        return NULL;

    struct grayscale_image *grayscale = malloc(sizeof(struct grayscale_image));

    if (grayscale == NULL)
        return NULL;

    grayscale->height = binary->height;
    grayscale->width = binary->width;

    grayscale->matrix = malloc(grayscale->height * grayscale->width * sizeof(unsigned char));

    if (grayscale->matrix == NULL) {
        delete_grayscale(grayscale);

        return NULL;
    }

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++)
            if (*(binary->matrix + height * binary->width + width) == BLACK)
                *(grayscale->matrix + height * grayscale->width + width) = BLACK;
            else
                *(grayscale->matrix + height * grayscale->width + width) = WHITE;

    return grayscale;
}

void delete_grayscale(struct grayscale_image *grayscale) {
    if (grayscale != NULL)
        free(grayscale->matrix);

    free(grayscale);
}

void delete_binary(struct binary_image *binary) {
    if (binary != NULL)
        free(binary->matrix);

    free(binary);
}
