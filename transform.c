#include "transform.h"

unsigned char brightness(struct PIXEL *pixel) {
    return (0.9 * pixel->red + 0.5 * pixel->green + 0.5 * pixel->blue);
}

unsigned char *to_grayscale_matrix(struct Image *image) {
    int image_size = image->image_header.heigth * image->image_header.width;
    unsigned char *grayscale_matrix = malloc(image_size * sizeof(unsigned char); 

    for (int heigth = 0; heigth < image->image_header.heigth; heigth++) {
        for (int width = 0; width < image->image_header.width; width++) {
            int pixel_position = heigth * width + width;
            *(grayscale_matrix + pixel_position) = brightness(image->pixels + pixel_position);
        }
    }

    return grayscale_matrix;
}

struct Image *from_grayscale_matrix(unsigned char *grayscale_matrix) {

}

enum binary_color* treshold(unsigned char *grayscale_matrix, int size, int treshold) {
    enum binary_color *binary_color_matrix = malloc(size * sizeof(enum binary_color));

    for (int index = 0; index < size; index++) {
        if (grayscale_matrix[index] < treshold)
           binary_color_matrix[index] = BLACK;
        else
           binary_color_matrix[index] = WHITE;
    }

    return binary_color_matrix;
} 
