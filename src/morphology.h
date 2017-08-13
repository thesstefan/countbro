/**
 * @file morphology.h
 *
 * This module provides the implementation of the basic morphological operations
 */

#include "transform.h"
#include "colors.h"
#include "image.h"

/**
 * @brief Representation of the kernel/structuring element used in morphological operations
 * 
 * The structuring element is a small binary image, i.e. a small matrix of pixels, each with a value
 * of zero or one.
 */
struct Kernel {
    char *kernel;/**The shape of the structuring element specified by the pattern of ones and zeroes*/ 
    int width;/**<The width of the structuring element*/
    int height;/**<The height of the structuring element*/
};

/**
 * @brief Enum type which stores the state of the kernel in relation with the image
 *
 * When a structuring element is placed in a binary image, each of its pixels is associated with the
 * correspoinding pixel of the neighourhood under the structuring element.
 *
 * The structuring element is said to FIT the image if, for each of its pixels set to 1, the corresponding
 * image pixel is also 1.
 *
 * Similarly, a structuring element is said to HIT, or intersect, an image if, at least for one of its
 * pixels set to 1 the corresponding image pixel is also 1.
 *
 * A structuring element is said to be OUT the image if, none of its piels mach the corresponding image 
 * pixels.
 */ 
enum kernel_state {
    FIT,/**<The kernel fits the image*/
    HIT,/**<The kernel hits the image*/ 
    OUT/**<The kernel is out of the image*/
};

/**
 * @brief Create a new square kernel with a given size
 *
 * A common practice is to have odd dimensions of the structuring matrix and the origin defined
 * as the centre of the matrix.
 *
 * @param size The size of the sides of the square
 *
 * @return Pointer to the created kernel
 */
struct Kernel *square_kernel(int size);

/**
 * @brief Delete a kernel
 *
 * @param kernel The kernel to be deleted
 *
 * @return none
 */
void delete_kernel(struct Kernel *kernel);

/**
 * @brief The implementation of erosion, fundamental morphological operation
 *
 * The erosion of a binary image I by a structuring element S produces a new binary image G
 * with ones in all locations (x,y) of a structuring element's origin at which that structuring 
 * elemet S fits the input image F, i.e. g(x,y) = 1 if S fits F and 0 otherwise, repeating for all
 * pixel coordinates (x,y).
 *
 * Erosion removes small-scale details from a binary image but simultaneously reduces the size of 
 * regions of interest
 *
 * @param image The binary image to which we apply the erosion
 *
 * @param kernel The structuring element used to apply the erosion
 *
 * @return none
 */
void erosion(struct binary_image *image, struct Kernel *kernel);

/**
 * @brief The implementation of erosion, fundamental morphological operation
 *
 * The dilation of a binary image F by a structuring element S produces a new binary image G
 * with ones in all locations of a structuring element's origin at which that structuring 
 * element S hits the input image F, i.e. g(x,y) = 1 if S hits F and 0 otherwise, repeating for all
 * pixel coordinates (x,y).
 *
 * Dilation has the opposite effect to erosion -- it adds a layer of pixels to  both the inner and outer 
 * boundaries of regions.
 *
 * @param image The binary image to which we apply the dilation
 *
 * @param kernel The structuring element used to apply the dilation
 *
 * @return none
 */ 
void dilation(struct binary_image *image, struct Kernel *kernel);

/**
 * @brief The implementation of opening, compound morphological operation
 *
 * The opening of an image F by a structuring element S is an erosion followed by a dilation
 *
 * Opening is so called because it can open up a gap between objects connected by a thin bridge of
 * pixels. Any regions that have survived the erosion are restored to their original size by the 
 * dilation.
 *
 * @param image The binary image to which we apply the opening
 *
 * @param kernel The structuring element used to apply the opening
 */
void opening(struct binary_image *image, struct Kernel *kernel);

/**
 * @brief The implementation of closing, compound morphological operation
 *
 * The closing of an image F by a structuring element S is a dilation followed by an erosion
 *
 * Closing is so called because it can fill holes in the regions while keeping the initial
 * region sizes.  
 *
 * @param image The binary image to which we apply the closing
 *
 * @param kernel The structuring element used to apply the closing
 */
void closing(struct binary_image *image, struct Kernel *kernel);
