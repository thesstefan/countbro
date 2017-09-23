#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "errors.h"

struct Vector *vector_create() {
    struct Vector *new_vector = malloc(sizeof(struct Vector));

    new_vector->capacity = VECTOR_INIT_CAPACITY;
    new_vector->size = 0;
    new_vector->items = malloc(sizeof(int) * new_vector->capacity);

    return new_vector;
}

int vector_resize(struct Vector *vector, int capacity) {
    int *items = realloc(vector->items, sizeof(int) * capacity);

    if (items == NULL)
        return MEMORY_ERROR;

    vector->items = items;
    vector->capacity = capacity;

    return SUCCESS;
}

int vector_add(struct Vector *vector, int item) {
    if (vector == NULL)
        return NULL_VECTOR;

    if (vector->capacity == vector->size) {
        if (vector_resize(vector, vector->capacity * 2) != SUCCESS)
            return MEMORY_ERROR;
    }

    vector->items[vector->size] = item;
    vector->size += 1;

    return SUCCESS;
}

int vector_set(struct Vector *vector, int index, int item) {
    if (vector == NULL)
        return NULL_VECTOR;

    if (index < 0 || index >= vector->size)
        return OUT_OF_BOUNDS;

    vector->items[index] = item; 

    return SUCCESS;
}

int vector_get(struct Vector *vector, int index, int *value) {
    if (vector == NULL)
        return NULL_VECTOR;

    if (vector->size == 0)
        return EMPTY_VECTOR;

    if (index < 0 || index >= vector->size) 
        return OUT_OF_BOUNDS;

    *value = vector->items[index];

    return SUCCESS;
}

int vector_remove(struct Vector *vector, int index) {
    if (vector == NULL)
        return NULL_VECTOR;

    if (vector->size == 0)
        return EMPTY_VECTOR;

    if (index < 0 || index >= vector->size)
        return OUT_OF_BOUNDS;

    for (int shift_index = index; shift_index < vector->size - 1; shift_index++)
        vector->items[shift_index] = vector->items[shift_index + 1];

    vector->items[vector->size - 1] = -1;
    vector->size--;

    if (vector->size > 0 && vector->size == vector->capacity / 4)
        if (vector_resize(vector, vector->capacity / 2) != SUCCESS)
             return MEMORY_ERROR;

    return SUCCESS;
}

void vector_free(struct Vector *vector) {
    free(vector->items);
    free(vector);
}
