#include "image.h"
#include "morphology.h"
#include "transform.h"
#include "labeling.h"

#include <string.h>

#define COLORS_NUMBER 6

const struct PIXEL color[COLORS_NUMBER] = {{255, 0, 0}, // RED
                                           {0, 255, 0}, // LIME
                                           {0, 0, 255}, // BLUE
                                           {255, 0, 255}, // YELLOW
                                           {0, 255, 255}, // CYAN
                                           {255, 0, 255}, // MAGENTA
};

struct PIXEL get_color(int number) {
    return color[number % COLORS_NUMBER];
}

void print_labels(struct Labels *labels) {
    for (int height = 0; height < labels->height; height++) {
        for (int width = 0; width < labels->width; width++) {
            int label = *(labels->matrix + height * labels->width + width);

            printf("%d ", label);
        }

        printf("\n");
    }
}

void colorize(struct Image *image, struct Labels *labels) {
    for (int height = 0; height < labels->height; height++)
        for (int width = 0; width < labels->width; width++) {
            int label = *(labels->matrix + height * labels->width + width);

            if (label != 0)
                *(image->pixels + height * image->image_header.width + width) = get_color(label);
        }
}

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file("/home/stefan/code/data/wow.bmp");

    struct grayscale_image *grayscale = to_grayscale_matrix(image);

    struct binary_image *binary = treshold(grayscale, 170);

    delete_grayscale(grayscale);

    /*
    struct Kernel *opening_kernel = square_kernel(3);
    struct Kernel *closing_kernel = square_kernel(5);

    opening(binary, opening_kernel);
    closing(binary, closing_kernel);
    */

    struct Labels *labels = labeling(binary);

    //print_labels(labels);

    /*
    delete_kernel(opening_kernel);
    delete_kernel(closing_kernel);
    */

    // print_labels(labels);

    // delete_labels(labels);

    struct grayscale_image *tresholded_grayscale = from_binary_to_grayscale(binary);

    delete_binary(binary);
    
    from_grayscale_matrix(tresholded_grayscale, image);

    delete_grayscale(tresholded_grayscale);

    colorize(image, labels);

    delete_labels(labels);

    write_image_to_file(image, argv[2]);

    delete_image(image);

    return 0;
}
