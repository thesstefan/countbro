#include "image.h"
#include "morphology.h"
#include "transform.h"
#include "labeling.h"
#include <string.h>

void print_labels(struct Labels_list *labels) {
    for (int height = 0; height < labels->height; height++) {
        for (int width = 0; width < labels->width; width++)
            printf("%d ", *(labels->matrix + labels->width * height + width));

        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    struct Image *image = read_image_from_file(argv[1]);

// GOOD
    struct grayscale_image *grayscale = to_grayscale_matrix(image);

    struct binary_image *binary = treshold(grayscale, 150);

// 94
/*
    struct Kernel *opening_kernel = square_kernel(3);
    struct Kernel *closing_kernel = square_kernel(5);

    opening(binary, opening_kernel);
    closing(binary, closing_kernel);
*/
    struct Labels_list *labels = labeling(binary);

    print_labels(labels);

    struct grayscale_image *tresholded_grayscale = from_binary_to_grayscale(binary);

   from_grayscale_matrix(tresholded_grayscale, image);

   write_image_to_file(image, argv[2]);

   delete_image(image);

   free(grayscale);
   free(binary);
   /*
   free(opening_kernel);
   free(closing_kernel);
   */
   free(tresholded_grayscale);

    return 0;
}
