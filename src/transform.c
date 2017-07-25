#include "transform.h"

unsigned char brightness(struct PIXEL *pixel) {
    return (0.9 * pixel->red + 0.5 * pixel->green + 0.5 * pixel->blue);
}

struct grayscale_image *to_grayscale_matrix(struct Image *image) {
    struct grayscale_image *grayscale = malloc(sizeof(struct grayscale_image)); 
    
    grayscale->height = image->image_header.height;
    grayscale->width = image->image_header.width;

    grayscale->matrix = malloc(grayscale->width * grayscale->height * sizeof(unsigned char));

    for (int height = 0; height < grayscale->height; height++)
        for (int width = 0; width < grayscale->width; width++)
            *(grayscale->matrix + height * grayscale->width + width) = brightness(image->pixels + height * image->image_header.width + width);

    return grayscale;
}

void from_grayscale_matrix(struct grayscale_image *grayscale, struct Image *image) {
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
}

struct binary_image *treshold(struct grayscale_image *grayscale, int treshold_constant) {
    struct binary_image *binary = malloc(sizeof(struct binary_image));

    binary->height = grayscale->height;
    binary->width = grayscale->width;

    binary->matrix = malloc(binary->height * binary->width * sizeof(enum binary_color));

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++)
            if (*(grayscale->matrix + height * grayscale->width + width) < treshold_constant)
                *(binary->matrix + height * binary->width + width) = WHITE;
            else
                *(binary->matrix + height * binary->width + width) = BLACK;

    return binary;
} 

struct grayscale_image *from_binary_to_grayscale(struct binary_image *binary) {
    struct grayscale_image *grayscale = malloc(sizeof(struct grayscale_image));

    grayscale->height = binary->height;
    grayscale->width = binary->width;

    grayscale->matrix = malloc(grayscale->height * grayscale->width * sizeof(unsigned char));

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++)
            if (*(binary->matrix + height * binary->width + width) == BLACK)
                *(grayscale->matrix + height * grayscale->width + width) = BLACK;
            else
                *(grayscale->matrix + height * grayscale->width + width) = WHITE;

    return grayscale;
}
