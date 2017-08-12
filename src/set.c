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
        if (item == set->representation->items[index])
            return 1;

    return 0;
}

int set_add(struct Set *set, int item) {
    if (set_find(set, item) == 0) {
        vector_add(set->representation, item);

        return 1;
    } else
        return 0;
}

int set_remove(struct Set *set, int item) {
    if (set_find(set, item))
        for (int index = 0; index < set->representation->size; index++)
            if (item == set->representation->items[index]) {
                vector_remove(set->representation, index);

                return 1;
            }

    return 0;
}

int set_cardinal(struct Set *set) {
    return set->representation->size;
}

int set_equals(struct Set *set_1, struct Set *set_2) {
    if (set_1->representation->size != set_2->representation->size) {
        return 0;
    } else {
        for (int index = 0; index < set_1->representation->size; index++)
            if (set_find(set_2, set_1->representation->items[index]) == 0)
                return 0;

        return 1;
    }
}

struct Set *set_intersection(struct Set *set_1, struct Set *set_2) {
    struct Set *intersection = set_create();

    for (int index = 0; index < set_1->representation->size; index++)
        if (set_find(set_2, set_1->representation->items[index]) == 1)
            set_add(intersection, set_1->representation->items[index]);

    return intersection;
}

struct Set *set_union(struct Set *set_1, struct Set *set_2) {
    struct Set *union_set = set_create();

    for (int index = 0; index < set_1->representation->size; index++)
        set_add(union_set, set_1->representation->items[index]);

    for (int index = 0; index < set_2->representation->size; index++)
        set_add(union_set, set_2->representation->items[index]);

    return union_set;
}

struct Set *set_difference(struct Set *set_1, struct Set *set_2) {
    struct Set *difference = set_create();

    for (int index = 0; index < set_1->representation->size; index++)
        if (set_find(set_2, set_1->representation->items[index]) == 0)
            set_add(difference, set_1->representation->items[index]);

    return difference;
}


    
    


