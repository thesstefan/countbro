// @file This module provides a basic int vector data type implementation

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
 * @return The new vector
 */
struct Vector *vector_create();

/** 
 * @brief Resize the vector
 *
 * @param vector   The vector to reallocate
 * @param capacity The capacity of the reallocated vector
 *
 * @return none
 */
void vector_resize(struct Vector *vector, int capacity);

/**
 * @brief Add an element to the vector
 *
 * @param vector The vector to add to
 * @param item   The item to add
 *
 * @return none  
 */  
void vector_add(struct Vector *vector, int item);

/**
 * @brief Set the value of an element, given the index
 *
 * @param vector The vector which contains the element
 * @param index  The index of the element
 * @param item   The value to be set
 *
 * @return none
 */
void vector_set(struct Vector *vector, int index, int item);

/**
 * @brief Get the value of an element, given the index
 *
 * @param vector The vector which contains the element
 * @param index  The index of the element
 *
 * @return The value of the element
 */
int vector_get(struct Vector *vector, int index);

/** 
 * @brief Delete an element of the vector
 *
 * @param vector The vector which contains the element to be deleted
 * @param index  The index of the element to be deleted
 *
 * @return none
 */
void vector_delete(struct Vector *vector, int index);

/**
 * @brief Delete a vector
 *
 * @param vector The vector to be deleted
 *
 * @return none
 */
void vector_free(struct Vector *vector);
