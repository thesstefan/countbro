/**
 * @file labelling.h
 *
 * This module provides a basic implementation of the connected component labeling algorithm
 */

#ifndef LABELLING_H
#define LABELLING_H

#if defined(CONNECTIVITY_8)
    #define NEEDED_NEIGHBORS 3
#elif defined(CONNECTIVITY_4)
    #define NEEDED_NEIGHBORS 2
#else
/** @brief The type of connectivity used in labelling which has 8 directions */
    #define CONNECTIVITY_8
/** @brief The number of neighbors needed to check based on the connectivity type */
    #define NEEDED_NEIGHBORS 3
#endif

/** @brief Macro used for the max number of labels used in labelling. Necessary for `set_min()` */
#define MAX_LABELS 1000000

/** @brief Representation of a label table */
struct Labels {
/** @brief Matrix of labels */
    int *matrix;
/** @brief Height of matrix */
    int height;
/** @brief Width of matrix */
    int width;
};

/** 
 * @brief The fuction returns a Labels structure, given a Binary image 
 *
 * The function is based on the standard CCA algorithm, having 2 phases : `first_pass()` and `second_pass()`
 *
 *
 *      The first_pass() raster scans the Binary image and labels every Pixel :
 *              If the Pixel is not background :
 *                      Get the neighbors of the pixel in a Set
 *                      If set_cardinal() of Set is 0, uniquely label the Pixel and continue
 *                      Otherwise, find the neighbor with the smallest label and assign it to the current Pixel
 *                      Store the equivalency between the labels
 *
 *      The second_pass() raster scans the Binary image and labels again every Pixel :
 *              If the Pixel is not background :
 *                      Relabel the Pixel with the lowest equivalent label
 *
 * @param image The Binary image to apply labeling() to
 *
 * @return Pointer to Labels structure on success
 * @return `NULL` on fail (`first_pass()` or `second_pass()` fail)
 */
struct Labels *labelling(struct Binary *image);

/**
 * @brief Delete a Labels structure
 *
 * @param labels The Labels structure to be deleted
 */
void delete_labels(struct Labels *labels);

#endif
