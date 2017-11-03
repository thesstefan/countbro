/**
 * @file morphology.h
 *
 * This module provides the implementation of the basic morphological operations
 */

#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "errors.h"
#include "transform.h"
#include "colors.h"
#include "image.h"

/**
 * @brief Macro to define the max size of a square Kernel
 */
#define KERNEL_MAX_SIZE 100

/**
 * @brief Representation of the kernel/structuring element used in morphological operations
 * 
 * The structuring element is a small binary image, i.e. a small matrix of pixels, each with a value
 * of zero or one.
 */
struct Kernel {
/** @brief The shape of the structuring element specified by the pattern of ones and zeroes */ 
    char *kernel;
/** @brief The width of the structuring element */
    int width;
/** @brief The height of the structuring element */
    int height;
};

/**
 * @brief Enum type which stores the state of the kernel in relation with the image
 *
 * When a Kernel is placed in a Binary image, each of its pixels is associated with the
 * correspoinding pixel of the neighourhood under the structuring element.
 *
 * The Kernel is said to @ref FIT the image if, for each of its pixels set to 1, the corresponding
 * image pixel is also 1.
 *
 * Similarly, a Kernel is said to @ref HIT, or intersect, an image if, at least for one of its
 * pixels set to 1 the corresponding image pixel is also 1.
 *
 * A structuring element is said to be @ref OUT the image if, none of its pixels match the corresponding image 
 * pixels.
 */ 
enum kernel_state {
/** @brief The Kernel fits the image */
    FIT,
/** @brief The Kernel hits the image */
    HIT, 
/** @brief The Kernel is out of the image*/
    OUT
};

/**
 * @brief Create a new square Kernel with a given size
 *
 * A common practice is to have odd dimensions of the structuring matrix and the origin defined
 * as the centre of the matrix.
 *
 * @param size = The size of the sides of the square Kernel
 *
 * @return Pointer to the created Kernel
 */
struct Kernel *square_kernel(int size);

/**
 * @brief Delete a Kernel
 *
 * @param kernel The Kernel to be deleted
 *
 * @return Void
 */
void delete_kernel(struct Kernel *kernel);

/**
 * @brief The implementation of erosion(), fundamental morphological operation
 *
 * The erosion() of a Binary image I by a Kernel K produces a new Binary image G
 * with ones in all locations (x,y) of a Kernel's origin at which that Kernel K
 * fits the input image I, i.e. g(x,y) = 1 if K fits I and 0 otherwise, repeating for all
 * pixel coordinates (x,y).
 *
 * Erosion removes small-scale details from a binary image but simultaneously reduces the size of 
 * regions of interest
 *
 * @param image The Binary image to which we apply the erosion
 * @param kernel The Kernel used to apply the erosion
 *
 * @return @ref SUCCESS on success 
 * @return @ref NULL_ERROR if @p image or @p kernel are `NULL` or `_copy_binary` returns `NULL` 
 */
int erosion(struct Binary *image, struct Kernel *kernel);

/**
 * @brief The implementation of dilation(), fundamental morphological operation
 *
 * The dilation() of a Binary image I by a Kernel K produces a new Binary image G
 * with ones in all locations of a Kernel's origin at which that Kernel K
 * hits the input image I, i.e. g(x,y) = 1 if K hits I and 0 otherwise, repeating for all
 * pixel coordinates (x,y).
 *
 * Dilation has the opposite effect to erosion() -- it adds a layer of pixels to  both the inner and outer 
 * boundaries of regions.
 *
 * @param image = The Binary image to which we apply the dilation
 * @param kernel = The Kernel used to apply the dilation
 *
 * @return @ref SUCCESS on success 
 * @return @ref NULL_ERROR if image or kernel are `NULL` or `_copy_binary` returns `NULL` 
 */ 
int dilation(struct Binary *image, struct Kernel *kernel);

/**
 * @brief The implementation of opening(), compound morphological operation
 *
 * The opening of a Binary image F by a Kernel K is an erosion() followed by a dilation()
 *
 * Opening is so called because it can open up a gap between objects connected by a thin bridge of
 * pixels. Any regions that have survived the erosion() are restored to their original size by the 
 * dilation().
 *
 * @param image = The Binary image to which we apply the opening
 * @param kernel = The Kernel used to apply the opening
 *
 * @return @ref SUCCESS on success
 * @return @ref FAIL if dilation() or erosion() fail
 * @return @ref NULL_ERROR if image or kernel are `NULL`
 */
int opening(struct Binary *image, struct Kernel *kernel);

/**
 * @brief The implementation of closing(), compound morphological operation
 *
 * The closing of a Binary image F by a Kernel K is a dilation() followed by an erosion()
 *
 * Closing is so called because it can fill holes in the regions while keeping the initial
 * region sizes.  
 *
 * @param image = The Binary to which we apply the closing
 * @param kernel = The Kernel used to apply the closing
 *
 * @return @ref SUCCESS on success
 * @return @ref FAIL if dilation() or erosion() fail
 * @return @ref NULL_ERROR if image or kernel are `NULL`
 */
int closing(struct Binary *image, struct Kernel *kernel);

#endif 
