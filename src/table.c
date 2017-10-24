#include <stdio.h>

#include "table.h"
#include "errors.h"

struct Table *table_create() {
    struct Table *new_table = malloc(sizeof(struct Table));

    if (new_table == NULL)
        return NULL;

    new_table->size = 0;
    new_table->capacity = TABLE_INIT_CAPACITY;

    new_table->cells = malloc(sizeof(struct Set *) * TABLE_INIT_CAPACITY);

    if (new_table->cells == NULL)
        return NULL;

    return new_table;
}

int table_resize(struct Table *table, int capacity) {
    struct Set **cells = realloc(table->cells, sizeof(struct Set *) *capacity);

    if (cells == NULL)
        return MEMORY_ERROR;

    table->cells = cells;
    table->capacity = capacity;

    return SUCCESS;
}

int table_add_entry(struct Table *table, struct Set *set) {
    if (table == NULL || set == NULL)
        return NULL_ERROR;

    if (table->size == table->capacity)
        if (table_resize(table, table->capacity * 2) != SUCCESS)
            return MEMORY_ERROR;

    table->cells[table->size] = set;
    table->size += 1;

    return SUCCESS;
}

void table_delete(struct Table *table) {
    if (table != NULL) {
        if (table->cells != NULL) {
            for (int index = 0; index < table->size; index++)
                set_delete(table->cells[index]);
        }

        free(table->cells);
    }

    free(table);
}

void table_print(struct Table *table) {
    for (int index = 0; index < table->size; index++) {
        printf("SET [%d] : ", index);
        print_set(table->cells[index]);
        printf("\n");
    }
}

/*
int main() {
    struct Set *set_1 = set_create();
    struct Set *set_2 = set_create();
    struct Set *set_3 = set_create();
    struct Set *set_4 = set_create();
    struct Set *set_5 = set_create();

    set_add(set_1, 1);
    set_add(set_1, 14);
    set_add(set_1, 98);
    set_add(set_1, 23);

    set_add(set_2, 2);
    set_add(set_2, 120310);

    set_add(set_3, 3);


    set_add(set_5, 3);
    set_add(set_5, 3);
    set_add(set_5, 13);
    set_add(set_5, 213);

    struct Table *table = table_create();

    table_add_entry(table, set_1);
    table_add_entry(table, set_2);
    table_add_entry(table, set_3);
    table_add_entry(table, set_4);
    table_add_entry(table, set_5);

    printf("SIZE : %d\nCAPACITY : %d\n", table->size, table->capacity);

    printf("SET 1 : ");
    print_set(table->cells[0]);
    printf("\n");
    printf("SET 2 : ");
    print_set(table->cells[1]);
    printf("\n");
    printf("SET 3 : ");
    print_set(table->cells[2]);
    printf("\n");
    printf("SET 4 : ");
    print_set(table->cells[3]);
    printf("\n");
    printf("SET 5 : ");
    print_set(table->cells[4]);
    printf("\n");

    table_delete(table);

    return 0;
}
*/
