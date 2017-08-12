#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct Vector *vector_create() {
    struct Vector *new_vector = malloc(sizeof(struct Vector));

    new_vector->capacity = VECTOR_INIT_CAPACITY;
    new_vector->size = 0;
    new_vector->items = malloc(sizeof(int) * new_vector->capacity);

    return new_vector;
}

void vector_resize(struct Vector *vector, int capacity) {

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
    if (vector->capacity == vector->size)
        vector_resize(vector, vector->capacity * 2);

    vector->items[vector->size] = item;

#ifdef DEBUG_ON
    printf("Added %d at index %d\n", item, vector->size);
#endif

    vector->size += 1;
}

void vector_set(struct Vector *vector, int index, int item) {
    if (index >= 0 && index < vector->size) {
        vector->items[index] = item; 

#ifdef DEBUG_ON
        printf("Element at index %d was set with the value %d", index, item);
#endif 
    } else  
       fprintf(stderr, "vector_set() ERROR : Element %d does not exist", index);
}

int vector_get(struct Vector *vector, int index) {
    if (index >= 0 && index < vector->size)
        return vector->items[index];
    else {
        fprintf(stderr, "vector_get() ERROR : Element %d does not exist", index);

        return -1;
    }
}

void vector_remove(struct Vector *vector, int index) {
    if (index >= 0 && index < vector->size) {
        for (int shift_index = index; shift_index < vector->size - 1; shift_index++)
            vector->items[shift_index] = vector->items[shift_index + 1];

        vector->items[vector->size - 1] = -1;
        vector->size--;

        if (vector->size > 0 && vector->size == vector->capacity / 4)
            vector_resize(vector, vector->capacity / 2);

        #ifdef DEBUG_ON
            printf("Deleted the element at index %d\n", index);
        #endif
    } else {
        fprintf(stderr, "vector_remove() ERROR : Element %d does not exist\n", index);
    }
}

void vector_free(struct Vector *vector) {
    free(vector->items);
    free(vector);

    #ifdef DEBUG_ON
        printf("The vector was deleted\n");
    #endif
}
