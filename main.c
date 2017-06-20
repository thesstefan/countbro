#include "image.h"
#include "morphology.h"
#include "transform.h"
#include <string.h>

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file(argv[1]);

    int size = image->image_header.heigth * image->image_header.width;

// GOOD
    double treshold_ct = 0;

    grayscale_image grayscale = to_grayscale_matrix(image, &treshold_ct);

    binary_image binary = treshold(grayscale, size, treshold_ct);

//    fill_square(binary, image->image_header.width, image->image_header.heigth, 3, BLACK, 3, 3);
    struct Kernel *kernel = square_kernel(10);
//
    dilation(binary, image->image_header.heigth, image->image_header.width, kernel); 

    grayscale_image tresholded_grayscale = from_binary_to_grayscale(binary, size);


// GOOD (?)
    from_grayscale_matrix(tresholded_grayscale, image);

// GOOD
    write_image_to_file(image, argv[2]);

//    delete_image(image);
 //   free(grayscale);

    return 0;
}
