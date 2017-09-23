#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "errors.h"

int vector_create_test() {
    struct Vector *vector = vector_create();

    if (vector == NULL || vector->size != 0 || vector->capacity != VECTOR_INIT_CAPACITY || vector->items == NULL)
        return FAIL;

    return SUCCESS;
}

int vector_add_test(struct Vector *vector) {
    if (vector_add(vector, 0) != SUCCESS)
        return FAIL;

    if (vector->size != 1 && vector->items[0] != 0)
        return FAIL;

    for (int index = 1; index < 5; index++) {
        if (vector_add(vector, index) != SUCCESS)
            return FAIL;

        if (vector->size != index && vector->items[index] != index)
            return FAIL;
    }

    vector = NULL;

    if (vector_add(vector, 0) != NULL_VECTOR)
        return FAIL;

    return SUCCESS;
}

int vector_get_test(struct Vector *vector) {
    int value = 0;

    vector->size = 0;

    if (vector_get(vector, 0, &value) != EMPTY_VECTOR)
        return FAIL;

    vector->size = 1;
    vector->items[0] = 1;

    if (vector_get(vector, 0, &value) != SUCCESS)
        return FAIL;

    if (value != 1)
        return FAIL;

    vector->size = 2;
    vector->items[1] = 1234;

    if (vector_get(vector, 0, &value) != SUCCESS)
        return FAIL;

    if (value != 1)
        return FAIL;

    if (vector_get(vector, 1, &value) != SUCCESS)
        return FAIL;

    if (value != 1234)
        return FAIL;

    if (vector_get(vector, -1, &value) != OUT_OF_BOUNDS && vector_get(vector, vector->size + 1, &value) != OUT_OF_BOUNDS)
        return FAIL;

    vector = NULL;

    if (vector_get(vector, 0, &value) != NULL_VECTOR)
        return FAIL;

    return SUCCESS;
}

int vector_set_test(struct Vector *vector) {
    vector->size = 1;
    vector->items[0] = 1;

    if (vector_set(vector, -1, 0) != OUT_OF_BOUNDS || vector_set(vector, vector->size + 1, 0) != OUT_OF_BOUNDS)
        return FAIL;

    if (vector_set(vector, 0, 100) != SUCCESS)
        return FAIL;

    if (vector->items[0] != 100)
        return FAIL;

    vector->size = 2;
    vector->items[1] = 9999;

    if (vector_set(vector, 1, 9999) != SUCCESS)
        return FAIL;

    if (vector->items[1] != 9999)
        return FAIL;

    vector = NULL;

    if (vector_set(vector, 0, 0) != NULL_VECTOR)
        return FAIL;

    return SUCCESS;
}

int vector_remove_test(struct Vector *vector) {
    vector->size = 0;

    if (vector_remove(vector, 0) != EMPTY_VECTOR)
        return FAIL;

    vector->size = 1;
    vector->items[0] = 1;

    if (vector_remove(vector, 0) != SUCCESS)
        return FAIL;

    if (vector->size != 0)
        return FAIL;

    if (vector->items[0] != -1)
        return FAIL;

    vector->size = 2;
    vector->items[0] = 10;
    vector->items[1] = 10000;

    if (vector_remove(vector, 1) != SUCCESS)
        return FAIL;

    if (vector->size != 1)
        return FAIL;

    if (vector->items[1] != -1 || vector->items[0] != 10)
        return FAIL;

    vector->size = 2;
    vector->items[0] = 10;
    vector->items[1] = 10000;

    if (vector_remove(vector, 0) != SUCCESS)
        return FAIL;

    if (vector->size != 1)
        return FAIL;

    if (vector->items[0] != 10000 && vector->items[1] != -1)
        return FAIL;

    vector = NULL;

    if (vector_remove(vector, 0) != NULL_VECTOR)
        return FAIL;

    return SUCCESS;
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
