#include "image.h"
#include <stdio.h>
#include <errno.h>

int _valid_pixels(struct Image *image) {
    for (int index = 0; index < image->image_header.width * image->image_header.height; index++)
        if (image->pixels + index != NULL) {
            if ((image->pixels + index)->red < 0 || (image->pixels + index)->red > 255)
                return 0;

            if ((image->pixels + index)->green < 0 || (image->pixels + index)->green > 255)
                return 0;

            if ((image->pixels + index)->blue < 0 || (image->pixels + index)->blue > 255)
                return 0;
        } else
            return 0;

    return 1;
}

int _valid_headers(struct Image *image) {
    if (image->file_header.file_marker_1 != 'B' || image->file_header.file_marker_2 != 'M')
        return 0;

    if (image->file_header.bmp_size < sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER))
        return 0;

    if (image->image_header.width <= 0 || image->image_header.height <= 0)
        return 0;

    if (image->image_header.planes != 1)
        return 0;

    if (image->image_header.compression_type != 0)
        return 0;

    if (image->image_header.pixel_per_meter_x < 0 || image->image_header.pixel_per_meter_y < 0)
        return 0;

    if (image->image_header.used_color_map_entries < 0 || image->image_header.significant_colors < 0)
        return 0;

    return 1;
}

/*
int valid_image(struct Image *image) {
    if (valid_headers(image) && valid_pixels(image))
        return 1;

    return 0;
}
*/

void _read_pixels(int height, int width, struct PIXEL *pixels, FILE *input) {
    int subpixels_per_line = width * 3;
    int required_padding = (subpixels_per_line % 4) ? 4 - subpixels_per_line % 4 : 0;
    int padding_dump = 0;

    for (int height_index = height - 1; height_index >= 0; height_index--) {
        fread(pixels + height_index * width, sizeof(struct PIXEL), width, input);
        fread(&padding_dump, sizeof(unsigned char), required_padding, input);
    }
}

void _write_pixels(int height, int width, struct PIXEL *pixels, FILE *output) {
    int subpixels_per_line = width * 3;
    int required_padding = (subpixels_per_line % 4) ? 4 - subpixels_per_line % 4 : 0;
    int padding_dump = 0;

    for (int height_index = height - 1; height_index >= 0; height_index--) {
        fwrite(pixels + height_index * width, sizeof(struct PIXEL), width, output);
        fwrite(&padding_dump, 1, required_padding, output);
    }
}

struct Image *_read_image(FILE *input) {
    struct Image *image = malloc(sizeof(struct Image));

    if (image == NULL)
        return NULL;

    size_t bytes_read = fread(&(image->file_header), 1, sizeof(struct FILE_HEADER), input);

    if (bytes_read != sizeof(struct FILE_HEADER)) {
        delete_image(image);

        return NULL;
    }

    bytes_read = fread(&(image->image_header), 1, sizeof(struct IMAGE_HEADER), input);

    if (bytes_read != sizeof(struct IMAGE_HEADER)) {
        delete_image(image);

        return NULL;
    }

    if (_valid_headers(image) != 1) {
        delete_image(image);
        
        return NULL;
    }

    image->pixels = malloc(image->image_header.height * image->image_header.width * sizeof(struct PIXEL));

    if (image->pixels == NULL) {
        delete_image(image);

        return NULL;
    }

    fseek(input, image->file_header.image_data_offset, SEEK_SET);

    _read_pixels(image->image_header.height, image->image_header.width, image->pixels, input);

    if (_valid_pixels(image) != 1) {
        delete_image(image);

        return NULL;
    }

    /*
    if (image->file_header.bmp_size != sizeof(struct FILE_HEADER) + sizeof(struct IMAGE_HEADER) + image->image_header.height * image->image_header.width * sizeof(struct PIXEL)) {
        delete_image(image);

        return NULL;
    }
    */

    return image;
}

void _write_image(struct Image *image, FILE *output) {
    fwrite(&(image->file_header), 1, sizeof(struct FILE_HEADER), output);
    fwrite(&(image->image_header), 1, sizeof(struct IMAGE_HEADER), output);

    int padding_dump = 0;
    int gap = image->file_header.image_data_offset - 54;

    for (int index = 0; index < gap; index++)
        fwrite(&padding_dump, 1, 1, output);

    _write_pixels(image->image_header.height, image->image_header.width, image->pixels, output);
}

struct Image *read_image_from_file(char *filename) {
    FILE *input = fopen(filename, "rb");

    if (input == NULL)
        return NULL;

    struct Image *image = _read_image(input);

    if (image == NULL)
        return NULL;

    fclose(input);

    return image;
}

int write_image_to_file(struct Image *image, char *filename) {
    FILE *output = fopen(filename, "wb");

    if (output == NULL) {
        fclose(output);

        return -1;
    }

    if (image == NULL) {
        fclose(output);

        return -1;
    }

    _write_image(image, output);
    fclose(output);

    return 0;
}

void delete_image(struct Image *image) {
    if (image != NULL)
        free(image->pixels);

    free(image);
}         
