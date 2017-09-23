/*
 * @file vector.h 
 *
 * This module provides a basic int vector data type implementation
 */

/**
 * @brief Macro used for the inital capacity of a vector
 */
#define VECTOR_INIT_CAPACITY 4

struct Vector {
    // Internal representation of a set
    int *items;
    int capacity;
    int size;
};

/**
 * @brief Create a new vector
 *
 * @return Pointer to the new vector on success
 *         NULL on failure (e.g. failed malloc())
 */
struct Vector *vector_create();

/**
 * @brief Add an element to the vector
 *
 * @param vector The vector to add to
 * @param item   The item to add
 *
 * @return 1 on success
 *         0 on failure (e.g. failed memory reallocation in vector_resize())  
 */  
int vector_add(struct Vector *vector, int item);

/**
 * @brief Set the value of an element, given the index
 *
 * @param vector The vector which contains the element
 * @param index  The index of the element
 * @param item   The value to be set
 *
 * @return 1 on success
 *         0 on failure (e.g. element index is out of bounds)
 */
int vector_set(struct Vector *vector, int index, int item);

/**
 * @brief Get the value of an element, given the index
 *
 * @param vector The vector which contains the element
 * @param index  The index of the element
 * @param value  The value of the element
 *
 * @return 1 on success
 *         0 on failure (e.g. element index is out of bounds)
 */
int vector_get(struct Vector *vector, int index, int *value);

/** 
 * @brief Delete an element of the vector
 *
 * @param vector The vector which contains the element to be deleted
 * @param index  The index of the element to be deleted
 *
 * @return 1 on success
 *         0 on failure (e.g. failed memory reallocation in vector_resize()
                         or  when the element to be deleted does not exist)
 */
int vector_remove(struct Vector *vector, int index);

/**
 * @brief Delete a vector
 *
 * @param vector The vector to be deleted
 *
 * @return none
 */
void vector_free(struct Vector *vector);
