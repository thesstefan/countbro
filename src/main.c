#include "image.h"
// #include "morphology.h"
#include "transform.h"
#include <string.h>

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file(argv[1]);

// GOOD

    double treshold_ct = 0;

    struct grayscale_image *grayscale = to_grayscale_matrix(image, &treshold_ct);

//    struct binary_image *binary = treshold(grayscale, treshold_ct);

//    fill_square(binary, image->image_header.width, image->image_header.height, 3, BLACK, 3, 3);
//    struct Kernel *kernel = square_kernel(10);
//
//    dilation(binary, image->image_header.height, image->image_header.width, kernel); 

//    struct grayscale_image *tresholded_grayscale = from_binary_to_grayscale(binary);


// GOOD (?)
//   from_grayscale_matrix(tresholded_grayscale, image);

// GOOD
   write_image_to_file(image, argv[2]);

//    delete_image(image);
 //   free(grayscale);


    return 0;
}
