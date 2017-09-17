#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define TEST_LIMIT 100

int vector_is_equal(struct Vector *vector_1, struct Vector *vector_2) {
    if (vector_1->size != vector_2->size)
        return 0;

    for (int index = 0; index < vector_1->size; index++)
        if (vector_1->items[index] != vector_2->items[index])
            return 0;

    return 1;
}

int vector_create_test() {
    struct Vector *vector = vector_create();

    if (vector == NULL || vector->size != 0 || vector->capacity != VECTOR_INIT_CAPACITY || vector->items == NULL)
        return 0;

    return 1;
}

int vector_add_test(struct Vector *sample) {
    struct Vector *vector = vector_create();

    for (int index = 0; index < TEST_LIMIT; index++) {
        if (vector_add(vector, index) == 0)
            return 0;

        if (vector->items[index] != index)
            return 0;
    }

    if (!vector_is_equal(vector, sample))
        return 0;

    return 1;
}

int vector_get_test(struct Vector *vector) {
    for (int index = 0; index < TEST_LIMIT; index++) {
        if (vector_get(vector, index) != index && vector->items[index] != index && index >= 0 && index < vector->size)
            return 0;
    }

    return 1;
}

int vector_set_test(struct Vector *vector) {
    for (int index = 0; index < TEST_LIMIT; index++) {
        if (vector_set(vector, index, 1) == 0 && index >= 0 && index < vector->size)
            return 0;

        if (vector->items[index] != 1 && index >= 0 && index < vector->size)
            return 0;
    }

    return 1;
}

int vector_remove_test(struct Vector *vector) {
    for (int index = 0; index < TEST_LIMIT; index++) {
        if (vector_remove(vector, 0) == 0)
            return 0;
    }
        
    if (vector->size != 0 || vector->capacity > 20)
        return 0;

    struct Vector *empty = vector_create();

    if (!vector_is_equal(empty, vector))
        return 0;

    return 1;
} 

void evaluate(int value) {
    if (value)
        printf("Success\n");
    else
        printf("Fail\n");
}

struct Vector *create_sample() {
    struct Vector *sample = vector_create();

    sample->size = TEST_LIMIT;
    sample->capacity = TEST_LIMIT;
    sample->items = malloc(sizeof(int) * TEST_LIMIT);

    for (int index = 0; index < TEST_LIMIT; index++)
        sample->items[index] = index;

    return sample;
}

int main() {
    // Padding
    printf("\n\n");

    struct Vector *sample = create_sample();

    printf("vector_create() test -> ");
    evaluate(vector_create_test()); 

    printf("vector_add() test -> ");
    evaluate(vector_add_test(sample));

    printf("vector_get() test -> ");
    evaluate(vector_get_test(sample));

    printf("vector_set() test -> ");
    evaluate(vector_set_test(sample));

    printf("vector_remove() test -> ");
    evaluate(vector_remove_test(sample));

    // Padding for the next test
    printf("\n\n");

    return 0; 
}
