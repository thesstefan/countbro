#include <assert.h>
#include <stdio.h>

#include "../src/vector.h"

int main() {
    struct Vector *vector = vector_create();

    printf("vector_create() test -> ");

    assert(vector != NULL);
    assert(vector->size == 0);
    assert(vector->capacity == VECTOR_INIT_CAPACITY);

    printf("Success\n");

    printf("vector_resize() test -> ");

    assert(vector_resize(vector, 10));
    assert(vector->capacity == 10);
    assert(vector_resize(vector, VECTOR_INIT_CAPACITY));
    assert(vector->capacity == VECTOR_INIT_CAPACITY);

    printf("Success\n");

    printf("vector_add() test -> ");

    for (int index = 0; index < 100; index++)
        assert(vector_add(vector, index));

    assert(vector->size == 100);
    assert(vector->capacity > 100);

    printf("Success\n");
    
    printf("vector_get() test -> ");

    for (int index = 0; index < 100; index++)
        assert(vector_get(vector, index) == index);

    printf("Success\n");

    printf("vector_set() test -> ");

    for (int index = 0; index < 100; index++) {
        assert(vector_set(vector, index, 1) == 1);
        assert(vector_get(vector, index) == 1);
    }
    
    printf("Success\n");

    printf("vector_remove() test -> ");

    for (int index = 99; index > 0; index--)
        assert(vector_remove(vector, index));

    assert(vector->size == 1);
    assert(vector->capacity < 20);

    printf("Success\n");

    return 0; 
}
