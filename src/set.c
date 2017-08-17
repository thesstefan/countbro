#include <stdlib.h>

#include "set.h"
#include "vector.h"

struct Set *set_create() {
    struct Set *new_set = malloc(sizeof(struct Set));

    new_set->representation = vector_create();

    return new_set;
}

void set_delete(struct Set *set) {
    vector_free(set->representation);

    free(set);
}

int set_find(struct Set *set, int item) {
    for (int index = 0; index < set->representation->size; index++)
        if (item == vector_get(set->representation, index))
            return 1;

    return 0;
}

int set_add(struct Set *set, int item) {
    if (set_find(set, item) == 1)
        return 0;

    vector_add(set->representation, item);

    return 1;
}

int set_remove(struct Set *set, int item) {
    if (set_find(set, item) == 0)
        return 0;

    for (int index = 0; index < set->representation->size; index++)
        if (item == vector_get(set->representation, index)) {
            vector_remove(set->representation, index);

            return 1;
        }
}

int set_cardinal(struct Set *set) {
    return set->representation->size;
}

int set_equals(struct Set *a, struct Set *b) {
    if (a->representation->size != b->representation->size)
        return 0;
        
    for (int index = 0; index < a->representation->size; index++)
        if (set_find(b, vector_get(a->representation, index)) == 0)
                return 0;

    return 1;
}

struct Set *set_intersection(struct Set *a, struct Set *b) {
    struct Set *intersection = set_create();

    for (int index = 0; index < a->representation->size; index++)
        if (set_find(b, vector_get(a->representation, index) == 1))
            set_add(intersection, vector_get(a->representation, index));

    return intersection;
}

struct Set *set_union(struct Set *a, struct Set *b) {
    struct Set *union_set = set_create();

    for (int index = 0; index < a->representation->size; index++)
        set_add(union_set, vector_get(a->representation, index));

    for (int index = 0; index < b->representation->size; index++)
        set_add(union_set, vector_get(b->representation, index));

    return union_set;
}

struct Set *set_difference(struct Set *a, struct Set *b) {
    struct Set *difference = set_create();

    for (int index = 0; index < a->representation->size; index++)
        if (set_find(b, vector_get(a->representation, index) == 0))
            set_add(difference, vector_get(a->representation, index));

    return difference;
}
