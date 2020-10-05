#include "image.h"
#include "morphology.h"
#include "transform.h"
#include "labelling.h"
#include "colors.h"
#include "colorize.h"

#include <string.h>

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file(argv[1]);
    struct Grayscale *grayscale = to_grayscale_matrix(image);
    struct Binary *binary = threshold(grayscale, 40);

    delete_grayscale(grayscale);

    struct Labels *labels = labelling(binary);

    struct Grayscale *thresholded_grayscale = from_binary_to_grayscale(binary);

    delete_binary(binary);
    
    from_grayscale_matrix(thresholded_grayscale, image);

    delete_grayscale(thresholded_grayscale);

    colorize(image, labels);

    delete_labels(labels);

    write_image_to_file(image, argv[2]);
    delete_image(image);

    return 0;
}
