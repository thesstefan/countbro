/**
 * @file vector.h 
 *
 * This module provides a basic int Vector data type implementation
 */

/** @brief Macro used for the inital capacity of a Vector */
#define VECTOR_INIT_CAPACITY 4

/** @brief Representation of a vector */
struct Vector {
/** @brief Items of a vector */
    int *items;
/** @brief Capacity of a vector */
    int capacity;
/** @brief Size of a vector */
    int size;
} __attribute__((__packed__));

/**
 * @brief Create a new Vector
 *
 * @return Pointer to the new Vector on success
 * @return `NULL` on failure (e.g. failed `malloc()`)
 */
struct Vector *vector_create();

/**
 * @brief Delete a Vector
 *
 * @param vector The Vector to be deleted
 */
void vector_delete(struct Vector *vector);

/**
 * @brief Add an element to a Vector
 *
 * @param vector The Vector to add to
 * @param item The item to add
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR when @p vector is `NULL`
 * @return @ref MEMORY_ERROR on `realloc()` fail
 */  
int vector_add(struct Vector *vector, int item);

/**
 * @brief Set the value of an element of a Vector, given the index
 *
 * @param vector The Vector which contains the element
 * @param index  The index of the element
 * @param item   The value to be set
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR when @p vector is `NULL`
 * @return @ref OUT_OF_BOUNDS when @p index is out of bounds
 */
int vector_set(struct Vector *vector, int index, int item);

/**
 * @brief Get the value of an element of a Vector, given the index
 *
 * @param vector The Vector which contains the element
 * @param index  The index of the element
 * @param value  The value of the element
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR when @p vector is `NULL`
 * @return @ref OUT_OF_BOUNDS when @p index is out of bounds
 * @return @ref EMPTY_ERROR when @p vector is empty
 */
int vector_get(struct Vector *vector, int index, int *value);

/** 
 * @brief Delete an element of a Vector
 *
 * @param vector The Vector which contains the element to be deleted
 * @param index  The index of the element to be deleted
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR when @p vector is `NULL`
 * @return @ref OUT_OF_BOUNDS when @p index is out of bounds
 * @return @ref MEMORY_ERROR when `realloc()` fails
 * @return @ref EMPTY_ERROR when @p vector is empty
 */
int vector_remove(struct Vector *vector, int index);
