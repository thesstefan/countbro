#include "image.h"
#include "morphology.h"
#include "transform.h"
#include <string.h>

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file(argv[1]);

// GOOD
    struct grayscale_image *grayscale = to_grayscale_matrix(image);

    struct binary_image *binary = treshold(grayscale, 94);

    struct Kernel *opening_kernel = square_kernel(3);
    struct Kernel *closing_kernel = square_kernel(5);

    opening(binary, opening_kernel);
    closing(binary, closing_kernel);

    struct grayscale_image *tresholded_grayscale = from_binary_to_grayscale(binary);


// GOOD (?)
   from_grayscale_matrix(tresholded_grayscale, image);

// GOOD
   write_image_to_file(image, argv[2]);

//    delete_image(image);
 //   free(grayscale);


    return 0;
}
