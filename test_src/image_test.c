#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "image.h"

unsigned char *raw_read_headers(FILE *input) {
    unsigned char *headers = malloc(sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER));
    
    if (headers == NULL) {
        free(headers);

        return NULL;
    }

    fread(headers, 1, sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER), input);

    return headers;
}

int get_headers_state(struct Image *image, FILE *input) {
    unsigned char *raw_headers = raw_read_headers(input);

    if (raw_headers == NULL)
        return FAIL;

    unsigned char *struct_headers = malloc(sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER));

    if (struct_headers == NULL) {
        free(struct_headers);
        free(raw_headers);

        return FAIL;
    }

    memcpy(struct_headers, image, sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER));

    for (int index = 0; index < sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER); index++)
        if (*(struct_headers + index) != *(raw_headers + index)) {
            free(struct_headers);
            free(raw_headers);

            return FAIL;
        }

    free(struct_headers);
    free(raw_headers);

    return SUCCESS;
}

struct PIXEL *raw_read_pixels(int height, int width, FILE *input) {
    struct PIXEL *pixels = malloc(sizeof(struct PIXEL) * height * width);

    if (pixels == NULL)
        return NULL;

    int subpixels_per_line = width * 3;
    int required_padding = (subpixels_per_line % 4) ? 4 - subpixels_per_line % 4 : 0;
    int padding_dump = 0;

    for (int height_index = height - 1; height_index >= 0; height_index--) {
        fread(pixels + height_index * width, sizeof(struct PIXEL), width, input);
        fread(&padding_dump, sizeof(unsigned char), required_padding, input);
    }

    return pixels;
}

int get_pixels_state(struct Image *image, FILE *input) {
    struct PIXEL *pixels = raw_read_pixels(image->image_header.height, image->image_header.width, input);

    if (pixels == NULL)
        return FAIL;

    for (int index = 0; index < image->image_header.height * image->image_header.width; index++)
        if (((pixels + index)->red != (image->pixels + index)->red) || ((pixels + index)->green != (image->pixels + index)->green) || ((pixels + index)->blue != (image->pixels + index)->blue)) {
            free(pixels);

            return FAIL;
        }

    free(pixels);
        
    return SUCCESS;
}

int standard_read_image(char *filename) {
    struct Image *image = read_image_from_file(filename);

    FILE *input = fopen(filename, "rb");

    if (get_headers_state(image, input) != SUCCESS) {
        delete_image(image);
        fclose(input);

        return FAIL;
    }

    if (get_pixels_state(image, input) != SUCCESS) {
        delete_image(image);
        fclose(input);
        
        return FAIL;
    }

    delete_image(image);
    fclose(input);

    return SUCCESS;
}

int read_non_existent_file() {
    struct Image *image = read_image_from_file("Nothing");

    if (image != NULL) {
        delete_image(image);

        return FAIL;
    }

    return SUCCESS;
}


int read_image_test(char *filename) {
    if (read_non_existent_file() != SUCCESS)
        return FAIL;

    if (standard_read_image(filename) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

int main() {
    printf("\n\n");

    printf("read_image_from_file() test -> ");
    evaluate(read_image_test("data/image_read_test_file"));

    printf("\n\n");

    return 0;
}

