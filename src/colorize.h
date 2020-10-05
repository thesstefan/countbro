/**
 * @file colorize.h
 *
 * This module provides colorize()
 */

#ifndef COLORIZE_H
#define COLORIZE_H

#include "image.h"
#include "labelling.h"

/** @brief The number of colors used to colorize */
#define COLORS_NUMBER 13

/** 
 * @brief Function which colorizes shapes of an Image, a Labels structure being given.
 *
 * @param image The Image to be colorized
 * @param labels The Labels structure to be colorized after
 */
void colorize(struct Image *image, struct Labels *labels);

#endif
