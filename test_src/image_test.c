#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "image.h"

int equal_headers(unsigned char *header_1, unsigned char *header_2) {
    for (int index = 0; index < sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER); index++)
        if (*(header_1 + index) != *(header_2 + index))
            return 0;

    return 1;
}

int equal_pixels(struct PIXEL *pixels_1, struct PIXEL *pixels_2, int size) {
    for (int index = 0; index < size; index++)
        if ((pixels_1 + index)->red != (pixels_2 + index)->red || (pixels_1 + index)->green != (pixels_2 + index)->green || (pixels_1 + index)->blue != (pixels_2 + index)->blue)
            return 0;

    return 1;
}

void read_pixels(int height, int width, struct PIXEL *pixels, FILE *input) {
    int subpixels_per_line = width * 3;
    int required_padding = (subpixels_per_line % 4) ? 4 - subpixels_per_line % 4 : 0;
    int padding_dump = 0;

    for (int height_index = height - 1; height_index >= 0; height_index--) {
        fread(pixels + height_index * width, sizeof(struct PIXEL), width, input);
        fread(&padding_dump, sizeof(unsigned char), required_padding, input);
    }
}

int read_image_test(char *filename) {
    struct Image *image = read_image_from_file("Non-existent file");

    if (image != NULL) {
        delete_image(image);

        return FAIL;
    }

    image = read_image_from_file(filename);

    if (image == NULL)
        return FAIL;

    FILE *input = fopen(filename, "rb");
    fseek(input, 0, SEEK_SET);
    
    if (input == NULL) {
        delete_image(image);

        return FAIL;
    }
 
    unsigned char *headers = malloc(sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER));

    if (headers == NULL)
        return FAIL;

    fread(headers, 1, sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER), input);

    unsigned char *struct_headers = malloc(sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER));

    if (struct_headers == NULL) {
        free(headers);

        return FAIL;
    }

    memcpy(struct_headers, image, sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER));

    if (equal_headers(headers, struct_headers) != 1) {
        free(headers);
        free(struct_headers);

        return FAIL;
    }

    free(headers);
    free(struct_headers);

    fseek(input, image->file_header.image_data_offset, SEEK_SET);

    struct PIXEL *pixels = malloc(image->image_header.height * image->image_header.width * sizeof(struct PIXEL));

    read_pixels(image->image_header.height, image->image_header.width, pixels, input);

    if (equal_pixels(pixels, image->pixels, image->image_header.height * image->image_header.width) != 1) {
        free(pixels);

        return FAIL;
    }

    free(pixels);

    delete_image(image);

    fclose(input);

    return SUCCESS;
}
        
int main() {
    printf("\n\n");

    printf("read_image_from_file() test -> ");
    evaluate(read_image_test("/home/stefan/code/data/image_read_test_file"));

    printf("\n\n");

    return 0;
}

