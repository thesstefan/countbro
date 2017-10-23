#include <stdio.h>

#include "image.h"
#include "transform.h"
#include "labeling.h"
#include "errors.h"

int empty_image_labeling() {
    struct Labels *labels = labeling(NULL);

    if (labels != NULL)
        return FAIL;

    return SUCCESS;
}

int standard_image_labeling(char *filename) {
    struct Image *image = read_image_from_file(filename);

    if (image == NULL)
        return FAIL;

    struct grayscale_image *grayscale = to_grayscale_matrix(image);

    if (grayscale == NULL)
        return FAIL;

    struct binary_image *binary = treshold(grayscale, 100);

    if (binary == NULL)
        return FAIL;

    struct Labels *labels = labeling(binary);

    if (labels == NULL)
        return FAIL;

    return SUCCESS;
}

int labeling_test(char *filename) {
    if (empty_image_labeling() != SUCCESS)
        return FAIL;

    if (standard_image_labeling(filename) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

int main() {
    printf("labeling() test -> ");
    evaluate(labeling_test("/home/stefan/code/data/standard"));

    return 0;
}

