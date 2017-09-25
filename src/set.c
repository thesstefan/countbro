#include <stdlib.h>

#include "set.h"
#include "errors.h"
#include "vector.h"

#include <stdio.h>

struct Set *set_create() {
    struct Set *new_set = malloc(sizeof(struct Set));

    new_set->representation = vector_create();

    return new_set;
}

void set_delete(struct Set *set) {
    vector_free(set->representation);

    free(set);
}

int set_cardinal(struct Set *set) {
    if (set == NULL)
        return -1;

    if (set->representation == NULL)
        return -1;

    return set->representation->size;
}

int set_find(struct Set *set, int item) {
    if (set == NULL)
        return -1;

    if (set->representation == NULL)
        return -1;

    if (set_cardinal(set) == 0)
        return 1;

    for (int index = 0; index < set_cardinal(set); index++) {
        int value = 0;

        if (vector_get(set->representation, index, &value) != SUCCESS)
            return -1;

        if (item == value)
            return 0;
    }

    return 1;
}

int set_add(struct Set *set, int item) {
    if (set == NULL)
        return -1;

    if (set->representation == NULL)
        return -1;

    if (set_find(set, item) == SUCCESS)
        return 1;

    if (vector_add(set->representation, item) != SUCCESS)
        return -1;

    return 0;
}

int set_remove(struct Set *set, int item) {
    if (set == NULL)
        return -1;

    if (set->representation == NULL)
        return -1;

    if (set_cardinal(set) == 0)
        return -1;

    if (set_find(set, item) != 0)
        return 1;

    for (int index = 0; index < set->representation->size; index++) {
        int value = 0;

        if (vector_get(set->representation, index, &value) != SUCCESS)
            return -1;

        if (item == value) {
            if (vector_remove(set->representation, index) != SUCCESS)
                return -1;

            return 0;
        }
    }
    
    return -1;
}

int set_equals(struct Set *a, struct Set *b) {
    if (a == NULL) 
        return -1;

    if (b == NULL)
        return -1;

    if (a->representation == NULL)
        return -1;

    if (b->representation == NULL)
        return -1;

    if (set_cardinal(a) != set_cardinal(b))
        return 1;
        
    for (int index = 0; index < set_cardinal(a); index++) {
        int value = 0;
        
        if (vector_get(a->representation, index, &value) != SUCCESS)
            return -1;

        if (set_find(b, value) != 0)
            return 1;
    }

    return 0;
}

struct Set *set_intersection(struct Set *a, struct Set *b) {
    if (a == NULL)
        return NULL;
    
    if (a->representation == NULL)
        return NULL;

    if (b == NULL)
        return NULL;

    if (b->representation == NULL)
        return NULL;

    struct Set *intersection = set_create();

    for (int index = 0; index < set_cardinal(a); index++) {
        int value = 0;

        if (vector_get(a->representation, index, &value) != SUCCESS)
            return NULL;

        if (set_find(b, value) == 0)
            if (set_add(intersection, value) == -1)
                return NULL;
    }

    return intersection;
}

struct Set *set_union(struct Set *a, struct Set *b) {
    if (a == NULL)
        return NULL;
    
    if (a->representation == NULL)
        return NULL;

    if (b == NULL)
        return NULL;

    if (b->representation == NULL)
        return NULL;
    
    struct Set *union_set = set_create();

    for (int index = 0; index < set_cardinal(a); index++) {
        int value = 0;

        if (vector_get(a->representation, index, &value) != SUCCESS) 
            return NULL;

        if (set_add(union_set, value) == -1)
            return NULL;
    }

    for (int index = 0; index < set_cardinal(b); index++) {
        int value = 0;

        if (vector_get(b->representation, index, &value) != SUCCESS) 
            return NULL;

        if (set_add(union_set, value) == -1)
            return NULL;
    }

    return union_set;
}

struct Set *set_difference(struct Set *a, struct Set *b) {
    if (a == NULL)
        return NULL;
    
    if (a->representation == NULL)
        return NULL;

    if (b == NULL)
        return NULL;

    if (b->representation == NULL)
        return NULL;

    struct Set *difference = set_create();

    for (int index = 0; index < set_cardinal(a); index++) {
        int value = 0;

        if (vector_get(a->representation, index, &value) != SUCCESS)
            return NULL;

        if (set_find(b, value) == 1)
            if (set_add(difference, value) == -1)
                return NULL;
    }

    return difference;
}
