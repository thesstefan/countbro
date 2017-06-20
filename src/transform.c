#include "transform.h"

unsigned char brightness(struct PIXEL *pixel) {
    return (0.9 * pixel->red + 0.5 * pixel->green + 0.5 * pixel->blue);
//    return (pixel->red + pixel->green + pixel->blue) / 3;
}

grayscale_image to_grayscale_matrix(struct Image *image, double *treshold_ct) {
    int image_size = image->image_header.heigth * image->image_header.width;
    unsigned char *grayscale_matrix = malloc(image_size * sizeof(unsigned char)); 
    long long sum = 0;

    for (int heigth = 0; heigth < image->image_header.heigth; heigth++) {
        for (int width = 0; width < image->image_header.width; width++) {
            int pixel_position = heigth * image->image_header.width + width;
            *(grayscale_matrix + pixel_position) = brightness(image->pixels + pixel_position);
            sum += brightness(image->pixels + pixel_position);
        }

    *treshold_ct = sum / image_size;
    }

    return grayscale_matrix;
}

void from_grayscale_matrix(grayscale_image grayscale_matrix, struct Image *image) {
    for (int heigth = 0; heigth < image->image_header.heigth; heigth++) {
        for (int width = 0; width < image->image_header.width; width++) {
            int pixel_position = heigth * image->image_header.width + width;

            (image->pixels + pixel_position)->red = grayscale_matrix[pixel_position];
            (image->pixels + pixel_position)->green = grayscale_matrix[pixel_position];
            (image->pixels + pixel_position)->blue = grayscale_matrix[pixel_position];
            
        }
    }
}

binary_image treshold(unsigned char *grayscale_matrix, int size, int treshold_constant) {
    binary_image binary_color_matrix = malloc(size * sizeof(enum binary_color));

    for (int index = 0; index < size; index++) {
        if ((int)grayscale_matrix[index] < treshold_constant)
           binary_color_matrix[index] = BLACK;
        else
           binary_color_matrix[index] = WHITE;
    }

    return binary_color_matrix;
} 

grayscale_image from_binary_to_grayscale(binary_image binary, int size) {
    grayscale_image grayscale = malloc(size * sizeof(unsigned char));

    for (int index = 0; index < size; index++) {
        if (binary[index] == BLACK)
            grayscale[index] = _BLACK;
        else
            grayscale[index] = _WHITE;
    }

    return grayscale;
}
