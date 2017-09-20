#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define TEST_LIMIT 100

int vector_create_test() {
    struct Vector *vector = vector_create();

    if (vector == NULL || vector->size != 0 || vector->capacity != VECTOR_INIT_CAPACITY || vector->items == NULL)
        return 0;

    return 1;
}

int vector_add_test(struct Vector *vector) {
    if (vector_add(vector, 0) == 0)
        return 0;

    if (vector->size != 1 && vector->items[0] != 0)
        return 0;

    for (int index = 1; index < 5; index++) {
        if (vector_add(vector, index) == 0)
            return 0;

        if (vector->size != index && vector->items[index] != index)
            return 0;
    }

    vector = NULL;

    if (vector_add(vector, 0) != 0)
        return 0;

    return 1;
}

int vector_get_test(struct Vector *vector) {
    if (vector_get(vector, 0) != -1)
        return 0;

    vector->size = 1;
    vector->items[0] = 1;

    if (vector_get(vector, 0) != 1)
        return 0;

    vector->size = 2;
    vector->items[1] = 1234;

    if (vector_get(vector, 0) != 1 && vector_get(vector, 1) != 1234) 
        return 0;

    if (vector_get(vector, -1) != -1 && vector_get(vector, vector->size + 1) != -1)
        return 0;
    
    vector = NULL;

    if (vector_get(vector, 0) != -1)
        return 0;

    return 1;
}

int vector_set_test(struct Vector *vector) {
    if (vector_set(vector, 0, 0) != 0)
        return 0;

    vector->size = 1;
    vector->items[0] = 1;

    if (vector_set(vector, -1, 0) != 0 || vector_set(vector, vector->size + 1, 0) != 0)
        return 0;

    if (vector_set(vector, 0, 100) != 1)
        return 0;

    if (vector->items[0] != 100)
        return 0;

    vector->size = 2;
    vector->items[1] = 9999;

    if (vector_set(vector, 1, 9999) != 1)
        return 0;

    if (vector->items[1] != 9999)
        return 0;

    vector = NULL;

    if (vector_set(vector, 0, 0) != 0)
        return 0;

    return 1;
}

int vector_remove_test(struct Vector *vector) {
    if (vector_remove(vector, 0) != 0)
        return 0;

    vector->size = 1;
    vector->items[0] = 1;

    if (vector_remove(vector, 0) != 1)
        return 0;

    if (vector->size != 0)
        return 0;

    if (vector->items[0] != -1)
        return 0;

    vector->size = 5;

    for (int index = 0; index < 5; index++) {
        vector->items[index] = index;

        if (vector_remove(vector, 0) != 1)
            return 0;

        if (vector->size != 4 - index)
            return 0;
    }

    if (vector->items[0] != -1)
        return 0;

    vector->size = 2;
    vector->items[0] = 10;
    vector->items[1] = 10000;

    if (vector_remove(vector, 1) != 1)
        return 0;

    if (vector->size != 1)
        return 0;

    if (vector->items[1] != -1 && vector->items[0] != 10)
        return 0;

    vector->size = 2;
    vector->items[0] = 10;
    vector->items[1] = 10000;

    if (vector_remove(vector, 0) != 1)
        return 0;

    if (vector->size != 1)
        return 0;

    if (vector->items[0] != 10000 && vector->items[1] != -1)
        return 0;

    vector = NULL;

    if (vector_remove(vector, 0) != 0)
        return 0;

    return 1;
} 

void evaluate(int value) {
    if (value)
        printf("Success\n");
    else
        printf("Fail\n");
}

int main() {
    // Padding
    printf("\n\n");

    printf("vector_create() test -> ");
    evaluate(vector_create_test()); 

    struct Vector *vector = vector_create();
    printf("vector_add() test -> ");
    evaluate(vector_add_test(vector));

    vector = vector_create();
    printf("vector_get() test -> ");
    evaluate(vector_get_test(vector));

    vector = vector_create();
    printf("vector_set() test -> ");
    evaluate(vector_set_test(vector));

    vector = vector_create();
    printf("vector_remove() test -> ");
    evaluate(vector_remove_test(vector));

    // Padding for the next test
    printf("\n\n");

    return 0; 
}
