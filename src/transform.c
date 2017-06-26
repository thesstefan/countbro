#include "transform.h"

unsigned char brightness(struct PIXEL pixel) {
    return (0.9 * pixel.red + 0.5 * pixel.green + 0.5 * pixel.blue);
}

struct grayscale_image *to_grayscale_matrix(struct Image *image, double *treshold_ct) {
    struct grayscale_image *grayscale = malloc(sizeof(struct grayscale_image)); 
    
    grayscale->height = image->image_header.height;
    grayscale->width = image->image_header.width;

    grayscale->matrix = malloc(grayscale->width * grayscale->height * sizeof(unsigned char));
    
    long long sum = 0;
    int image_size = image->image_header.height * image->image_header.width;

    for (int height = 0; height < image->image_header.height; height++) {
        for (int width = 0; width < image->image_header.width; width++) {
            grayscale->matrix[height][width] = brightness(image->pixels[height][width]);

            sum += brightness(image->pixels[height][width]);
        }

        *treshold_ct = sum / image_size;
    }

    return grayscale;
}

/*

void from_grayscale_matrix(struct grayscale_image *grayscale, struct Image *image) {
    for (int height = 0; height < image->image_header.height; height++) {
        for (int width = 0; width < image->image_header.width; width++) {
            if (grayscale->matrix[height][width] == BLACK)
                image->pixels[height][width] = {0,0,0};         // BLACK
            else 
                image->pixels[height][width] = {255, 255, 255}; // WHITE    
        }
    }
}

*/

struct binary_image *treshold(struct grayscale_image *grayscale, int treshold_constant) {
    struct binary_image *binary = malloc(sizeof(struct binary_image));

    binary->height = grayscale->height;
    binary->width = grayscale->width;

    binary->matrix = malloc(binary->height * binary->width * sizeof(enum binary_color));

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++)
            if ((int)grayscale->matrix[height][width] < treshold_constant)
                binary->matrix[height][width] = BLACK;
            else
                binary->matrix[height][width] = WHITE;

    return binary;
} 

struct grayscale_image *from_binary_to_grayscale(struct binary_image *binary) {
    struct grayscale_image *grayscale = malloc(sizeof(struct grayscale_image));

    grayscale->height = binary->height;
    grayscale->width = binary->width;

    grayscale->matrix = malloc(grayscale->height * grayscale->width * sizeof(unsigned char));

    for (int height = 0; height < binary->height; height++)
        for (int width = 0; width < binary->width; width++)
            if (binary->matrix[height][width] == BLACK)
                grayscale->matrix[height][width] = BLACK;
            else
                grayscale->matrix[height][width] = WHITE;

    return grayscale;
}
