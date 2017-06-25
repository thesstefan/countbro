#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct FILE_HEADER {
    unsigned char file_marker_1;
    unsigned char file_marker_2;
    unsigned int bmp_size;
    uint16_t unused_1;
    uint16_t unused_2;
    unsigned int image_data_offset;
} __attribute__((__packed__));

struct IMAGE_HEADER {
    unsigned int header_size;
    int width;
    int height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    unsigned int compression_type;
    unsigned int image_size;
    int pixel_per_meter_x;
    int pixel_per_meter_y;
    unsigned int used_color_map_entries;
    unsigned int significant_colors;
} __attribute__((__packed__));

struct PIXEL {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} __attribute__((__packed__));

struct Image {
    struct FILE_HEADER file_header;
    struct IMAGE_HEADER image_header;
    struct PIXEL **pixels;
};

struct Image *read_image_from_file(char *file_name);
void write_image_to_file(struct Image *image, char *file_name);
void delete_image(struct Image *image);

#endif
