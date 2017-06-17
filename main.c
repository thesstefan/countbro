#include "image.h"
#include "transform.h"

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file(argv[1]);
    grayscale_image grayscale = to_grayscale_matrix(image);
    binary_image binary = treshold(grayscale);

    delete_image(image);
    free(grayscale);

    return 0;
}
