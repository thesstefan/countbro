/**
 * @file image.h
 *
 * This module provides a basic BMP image implementation
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Representation of the file header of a BMP
 */
struct FileHeader {
    /** @brief The first value which identifies a file as BMP (usually 'B') */
    unsigned char file_marker_1;
    /** @brief The second value which identifies a file as BMP (usually 'M') */
    unsigned char file_marker_2;
    /** @brief The size of the image */
    unsigned int bmp_size;
    /** @brief The first reserved variable (usually completed by software) */
    uint16_t unused_1;
    /** @brief The second reserved variable (usually completed by software) */
    uint16_t unused_2;
    /** @brief The offset of the pixel table */
    unsigned int image_data_offset;
} /** @cond */ __attribute__((__packed__)) /** @endcond */;

/**
 * @brief Representation of the image header of a BMP
 */
struct ImageHeader {
    /** @brief The size of the image header */
    unsigned int header_size;
    /** @brief The width of the pixel table */
    int width;
    /** @brief The height of the pixel table */
    int height;
    /** @brief The number of color planes (must be 1) */
    uint16_t planes;
    /** @brief The number of bits per pixel. Typical values are 1, 4, 8, 16, 24 and 32. */
    uint16_t bits_per_pixel;
    /** @brief The compression method being used */
    unsigned int compression_type;
    /** @brief The size of the pixel table */
    unsigned int image_size;
    /** @brief The horizontal resolution of the image */
    int pixel_per_meter_x;
    /** @brief The vertical resolution of the image */
    int pixel_per_meter_y;
    /** @brief The number of colors in the color palette (0 to default 2^n) */
    unsigned int used_color_map_entries;
    /** @brief The number of important colors used, or 0 where all are important */
    unsigned int significant_colors;
} __attribute__((__packed__));

/**
 * @brief Representation of a pixel
*/
struct Pixel {
/**
 * @brief The quantity of red in the pixel
 */
    unsigned char red;
/**
 * @brief The quantity of green in the pixel
 */
    unsigned char green;
/**
 * @brief The quantity of blue in the pixel
 */
    unsigned char blue;
} __attribute__((__packed__));

/**
 * @brief Representation of a BMP
 */
struct Image {
/**
 * @brief The file header
 */
    struct FileHeader file_header;
/**
 * @brief The image header
 */
    struct ImageHeader image_header;
/**
 * @brief The pixel table
 */
    struct Pixel *pixels;
};

/**
 * @brief Read a image file into an Image structure
 *
 * @param file_name The name of the file to be read
 *
 * @return Pointer to Image structure on success
 * @return `NULL` on fail (`fopen()` fail or `_read_image()` fail) 
 */
struct Image *read_image_from_file(char *file_name);

/**
 * @brief Write an image from an Image structure to a file
 *
 * @param image The Image structure to be written
 * @param file_name The name of the file to be written into
 *
 * @return @ref SUCCESS on success
 * @return @ref FAIL on fail (@p image or @p file_name are `NULL`)
 */
int write_image_to_file(struct Image *image, char *file_name);

/**
 * @brief Delete an Image structure
 *
 * @param image The Image structure to be deleted
 */
void delete_image(struct Image *image);

#endif
