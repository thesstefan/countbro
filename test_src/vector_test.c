#include <assert.h>
#include <stdio.h>

#include "vector.h"

int vector_create_test() {
    printf("vector_create() test -> ");

    struct Vector *vector = vector_create();

    if (vector == NULL || vector->size != 0 || vector->capacity != VECTOR_INIT_CAPACITY || vector->items == NULL)
        return 0;

    return 1;
}

int vector_add_test() {
    printf("vector_add() test -> ");

    struct Vector *vector = vector_create();

    for (int index = 0; index < 100; index++)
        if (vector_add(vector, index) == 0)
            return 0;

    if (vector->size != 100 || vector->capacity < 100)
        return 0;

    return 1;
}

int vector_get_test() {
    printf("vector_get() test -> ");

    struct Vector *vector = vector_create();

    for (int index = 0; index < 100; index++) {
        vector_add(vector, index);

        if (vector_get(vector, index) != index && index >= 0 && index < vector->size)
            return 0;
    }

    return 1;
}

int vector_set_test() {
    printf("vector_set() test -> ");

    struct Vector *vector = vector_create();

    for (int index = 0; index < 100; index++) {
        vector_add(vector, index);

        if (vector_set(vector, index, 1) == 0 && index >= 0 && index < vector->size)
            return 0;

        if (vector_get(vector, index) != 1 && index >= 0 && index < vector->size)
            return 0;
    }

    return 1;
}

int vector_remove_test() {
    printf("vector_remove() test -> ");

    struct Vector *vector = vector_create();

    for (int index = 0; index < 100; index++) {
        vector_add(vector, index);

        if (vector_remove(vector, 0) == 0 && index >= 0 && index < vector->size) 
            return 0;
    }

    if (vector->size != 0 || vector->capacity > 20) 
       return 0;

   return 1;
} 

int main() {
    struct Vector *vector = vector_create();

    // Padding
    printf("\n\n");

    assert(vector_create_test()); 
    printf("Success\n");

    assert(vector_add_test());
    printf("Success\n");

    assert(vector_get_test());
    printf("Success\n");

    assert(vector_set_test());
    printf("Success\n");

    assert(vector_remove_test());
    printf("Success\n");

    // Padding for the next test
    printf("\n\n");

    return 0; 
}
