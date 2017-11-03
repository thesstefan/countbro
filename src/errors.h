/**
 * @file errors.h
 *
 * This module provides a set of error codes used to debug other modules
 */

/** 
 * @brief Macro to define success
 */
#define SUCCESS 0

/**
 * @brief Macro to define fail
 */
#define FAIL -1

/**
 * @brief Macro to define an error occured when an index is out of bounds
 */
#define OUT_OF_BOUNDS -2

/**
 * @brief Macro to define a memory error (usually malloc() fail)
 */
#define MEMORY_ERROR -3

/**
 * @brief Macro to define an error occured when a structure is NULL, even it
 * shouldn't
 */
#define NULL_ERROR -4

/**
 * @brief Macro to define that a container is empty (usually returned by functions
 * which use elements of the container
 */
#define EMPTY_ERROR -5

/**
 * @brief Macro to define that an element is found in a container (usually returned by set_find())
 */
#define FOUND 1

/**
 * @brief Macro to define that an element is not found in a container (usually returned by set_find())
 */
#define NOT_FOUND 2

/**
 * @brief Print output based on an error code
 *
 * @param status The error code to be interpreted
 */
void evaluate(int status);
