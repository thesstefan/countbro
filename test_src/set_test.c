#include <stdio.h>

#include "vector.h"
#include "set.h"
#include "errors.h"

int set_create_test() {
    struct Set *set = set_create();

    if (set == NULL)
        return FAIL;

    if (set->representation == NULL)
        return FAIL;

    if (set->representation->size != 0 || set->representation->capacity != VECTOR_INIT_CAPACITY || set->representation->items == NULL)
        return FAIL;

    return SUCCESS;
}

int set_cardinal_test(struct Set *set) {
    set->representation->size = 10;
    
    if (set_cardinal(set) != set->representation->size || set_cardinal(set) != 10)
        return FAIL;

    set->representation = NULL;

    if (set_cardinal(set) != -1)
        return FAIL;

    set = NULL;

    if (set_cardinal(set) != -1)
        return FAIL;

    return SUCCESS;
}

int set_find_test(struct Set *set) {
    vector_add(set->representation, 0);
    vector_add(set->representation, 1);
    vector_add(set->representation, 1000);

    if (set_find(set, 1) != 0 || set_find(set, 1) != 0 || set_find(set, 1000) != 0)
        return FAIL;

    if (set_find(set, 2) != 1)
        return FAIL;

    set->representation = NULL;

    if (set_find(set, 123) != -1)
        return FAIL;

    set = NULL;

    if (set_find(set, 123) != -1)
        return FAIL;

    return SUCCESS;
}

int set_add_test(struct Set *set) {
    vector_add(set->representation, 100);

    if (set_add(set, 100) != 1)
        return FAIL;

    if (set->representation->size != 1)
        return FAIL;

    if (set_add(set, 2) != 0)
        return FAIL;

    if (set->representation->size != 2)
        return FAIL;

    set->representation = NULL;

    if (set_add(set, 3) != -1)
        return FAIL;

    set = NULL;

    if (set_add(set, 4) != -1)
        return FAIL;

    return SUCCESS;
}

int set_remove_test(struct Set *set) {
    if (set_remove(set, 123) != -1)
        return FAIL;

    vector_add(set->representation, 1);

    if (set_remove(set, 2) != 1)
        return FAIL;

    if (set_remove(set, 1) != 0)
        return FAIL;


    if (set->representation->size != 0)
        return FAIL;

    set->representation = NULL;

    if (set_remove(set, 100) != -1)
        return FAIL;

    set = NULL;

    if (set_remove(set, 100) != -1)
        return FAIL;

    return SUCCESS;
}

int set_equals_test(struct Set *a, struct Set *b) {
    set_add(a, 1);
    set_add(a, 2);

    set_add(b, 2);
    
    if (set_equals(a, b) != 1)
        return FAIL;

    set_add(b, 1);

    if (set_equals(a, b) != 0)
        return FAIL;

    a->representation = NULL;

    if (set_equals(a, b) != -1)
        return FAIL;

    b->representation = NULL;

    if (set_equals(a, b) != -1)
        return FAIL;

    a = NULL;

    if (set_equals(a, b) != -1)
        return FAIL;

    b = NULL;

    if (set_equals(a, b) != -1)
        return FAIL;

    return SUCCESS;
}

int set_intersection_test(struct Set *a, struct Set *b) {
    vector_add(a->representation, 1);
    vector_add(a->representation, 2);

    vector_add(b->representation, 3);
    vector_add(b->representation, 1);

    struct Set *c = set_intersection(a, b);

    if (c != NULL) {
        if (c->representation->size != 1)
            return FAIL;

        if (c->representation->items[0] != 1)
            return FAIL;
    }

    c = set_intersection(b, a);

    if (c != NULL) {
        if (c->representation->size != 1)
            return FAIL;

        if (c->representation->items[0] != 1)
            return FAIL;
    }

    a->representation = NULL;

    if (set_intersection(a, b) != NULL)
        return FAIL;

    b->representation = NULL;

    if (set_intersection(a, b) != NULL)
        return FAIL;

    a = NULL;

    if (set_intersection(a, b) != NULL)
        return FAIL;

    b = NULL;

    if (set_intersection(a, b) != NULL)
        return FAIL;

    return SUCCESS;
}

int set_union_test(struct Set *a, struct Set *b) {
    vector_add(a->representation, 1);
    vector_add(a->representation, 2);

    vector_add(b->representation, 1);
    vector_add(b->representation, 3);

    struct Set *c = set_union(a, b);

    if (c != NULL) {
        if (c->representation->size != 3)
            return FAIL;

        if (c->representation->items[0] != 1 || c->representation->items[1] != 2 || c->representation->items[2] != 3)
                return FAIL;
    }

    c = set_union(b, a);

    if (c != NULL) {
        if (c->representation->size != 3)
            return FAIL;

        if (c->representation->items[0] != 1 || c->representation->items[1] != 3 || c->representation->items[2] != 2)
            return FAIL;
    }

    a->representation = NULL;

    if (set_union(a, b) != NULL)
        return FAIL;

    b->representation = NULL;

    if (set_union(a, b) != NULL)
        return FAIL;

    a = NULL;

    if (set_union(a, b) != NULL)
        return FAIL;

    b = NULL;

    if (set_union(a, b) != NULL)
        return FAIL;

    return SUCCESS;
}

int set_difference_test(struct Set *a, struct Set *b) {
    vector_add(a->representation, 1);
    vector_add(a->representation, 2);

    vector_add(b->representation, 3);
    vector_add(b->representation, 1);

    struct Set *c = set_difference(a, b);

    if (c != NULL) {
        if (c->representation->size != 1)
            return FAIL;

        if (c->representation->items[0] != 2)
            return FAIL;
    }

    c = set_difference(b, a);

    if (c != NULL) {
        if (c->representation->size != 1)
            return FAIL;

        if (c->representation->items[0] != 3)
            return FAIL;
    }

    a->representation = NULL;

    if (set_difference(a, b) != NULL)
        return FAIL;

    b->representation = NULL;

    if (set_difference(a, b) != NULL)
        return FAIL;

    a = NULL;

    if (set_difference(a, b) != NULL)
        return FAIL;

    b = NULL;

    if (set_difference(a, b) != NULL)
        return FAIL;

    return SUCCESS;
}

int main() {
    printf("set_create() test -> ");
    evaluate(set_create_test());

    struct Set *set = set_create();
    printf("set_cardinal() test -> ");
    evaluate(set_cardinal_test(set));

    set = set_create();
    printf("set_find() test -> ");
    evaluate(set_find_test(set));

    set = set_create();
    printf("set_add() test -> ");
    evaluate(set_add_test(set));

    set = set_create();
    printf("set_remove() test -> ");
    evaluate(set_remove_test(set));
    
    struct Set *a = set_create();
    struct Set *b = set_create();
    printf("set_equals() test -> ");
    evaluate(set_equals_test(a, b));

    a = set_create();
    b = set_create();
    printf("set_intersection() test -> ");
    evaluate(set_intersection_test(a, b));

    a = set_create();
    b = set_create();
    printf("set_union() test -> ");
    evaluate(set_union_test(a, b));

    a = set_create();
    b = set_create();
    printf("set_difference() test -> ");
    evaluate(set_difference_test(a, b));

    // Padding
    printf("\n\n");

    return 0;
}
