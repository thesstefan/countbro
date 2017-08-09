#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct Vector *vector_create() {
    struct Vector *new_vector = malloc(sizeof(vector));

    new_vector->capacity = VECTOR_INIT_CAPACITY;
    new_vector->count = 0;
    new_vector->items = malloc(sizeof(int) * new_vector->capacity);

    return new_vector;
}

struct Vector *vector_resize(struct Vector *vector, int capacity) {
    #ifdef DEBUG_ON
        printf("Vector resize : %d to %d\n", vector->capacity, capacity);
    #endif

    int *items = realloc(vector->items, sizeof(int) * capacity);

    if (items != NULL) {
        vector->items = items;
        vector->capacity = capacity;
    }
}

void vector_add(struct Vector *vector, int item) {
    if (vector->capacity = vector->count)
        vector = vector_resize(vector, vector->capacity * 2);

    vector->count++;

    vector->items[vector->count] = item;
}

void vector_set(struct Vector *vector, int index, int item) {
    if (index >= 0 && index < vector->count)
       v->items[index] = item;
    else  
       fprintf(stderr, "vector_set() ERROR : Element %d does not exist", index);
}

int vector_get(struct Vector *vector, int index) {
    if (index >= 0 && index < vector->count)
        return vector->items[index];
    else {
        fprintf(stderr, "vector_get() ERROR : Element %d does not exist", index);

        return -1;
    }
}

void vector_delete(struct Vector *vector, int index) {
    if (index >= 0 && index < vector->count) {
        for (int shift_index = index; shift_index < vector->count - 1; shift_index++)
            vector->items[shift_index] = vector->items[shift_index + 1];

        vector->items[vector_count - 1] = NULL;
        vector->count--;

        if (vector->count > 0 && vector->count == vector->capacity / 4)
            vector->resize(vector, vector->capacity / 2);
    } else {
        fprintf(stderr, "vector_remove() ERROR : Element %d does not exist", index);

        return -1;
    }
}

void vector_free(struct Vector *vector) {
    free(vector_items);
}
