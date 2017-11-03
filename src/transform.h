/**
 * @file transform.h
 *
 * This module provides simple implementations of various image types convertions
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <stdlib.h>

#include "colors.h"
#include "image.h"
#include "errors.h"

/** @brief Representation of a binary image */
struct Binary {
/** @brief The matrix of colors of the binary image */
    enum binary_color *matrix;
/** @brief The height of the binary_color matrix */
    int height;
/** @brief The width of the binary_color matrix */
    int width;
} __attribute__((__packed__));

/** @brief Representation of a grayscale image */
struct Grayscale {
/** @brief The matrix of grayscale colors */
    unsigned char *matrix;
/** @brief The height of the grayscale color matrix */
    int height;
/** @brief The width of the grayscale color matrix */
    int width;
} __attribute__((__packed__));

/**
 * @brief The function returns the brightness of a Pixel.
 *
 * It is based on a arbitrary formula.
 *
 * @param pixel The Pixel to be analyzed
 *
 * @return The brightness of @p pixel
 */
unsigned char brightness(struct Pixel *pixel);

/** 
 * @brief The function converts an Image structure into a Grayscale image.
 *
 * @param image The Image structure to be converted.
 *
 * @return Pointer to the Grayscale on success
 * @return `NULL` on failure (@p image is `NULL` or `malloc()` fails)
 */
struct Grayscale *to_grayscale_matrix(struct Image *image);

/**
 * @brief The function converts a Binary image to a Grayscale image.
 *
 * @param binary The Binary to be converted
 *
 * @return Pointer to the Grayscale on success
 * @return `NULL` on failure (@p binary is `NULL` or `malloc()` fail)
 */
struct Grayscale *from_binary_to_grayscale(struct Binary *binary);

/**
 * @brief The function thresholds a grayscale image based on a threshold constant
 *
 * The function converts a Grayscale image into a Binary image basing on a constant
 *
 * @param grayscale The Grayscale to be thresholded
 * @param threshold_constant The constant which defines the result 
 *
 * @return Pointer to the Binary image on success
 * @return `NULL` on failure (@p grayscale is `NULL` or @p threshold_constant is out of bounds or `malloc()` fail)
 */
struct Binary *threshold(struct Grayscale *grayscale, int threshold_constant);

/**
 * @brief The function converts an Grayscale image back to a Image structure
 *
 * @param grayscale_matrix The Grayscale to be converted
 * @param image The Image structure to be modified
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR if @p grayscale or @p image are `NULL`
 */
int from_grayscale_matrix(struct Grayscale *grayscale_matrix, struct Image *image);

/**
 * @brief Delete a Grayscale
 *
 * @param grayscale The Grayscale to be deleted
 */
void delete_grayscale(struct Grayscale *grayscale);

/**
 * @brief Delete a Binary
 *
 * @param binary The binary Binary to be deleted
 */
void delete_binary(struct Binary *binary);

#endif
