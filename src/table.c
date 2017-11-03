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

void table_delete(struct Table *table) {
    if (table != NULL) {
        if (table->cells != NULL) {
            for (int index = 0; index < table->size; index++) {
                set_delete(table->cells[index]);

                table->cells[index] = NULL;
            }
        }

        free(table->cells);

        table->cells = NULL;
    }

    free(table);

    table = NULL;
}



int _table_resize(struct Table *table, int capacity) {
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
        if (_table_resize(table, table->capacity * 2) != SUCCESS)
            return MEMORY_ERROR;

    table->cells[table->size] = set;
    table->size += 1;

    return SUCCESS;
}

int table_remove_entry(struct Table *table, int index) {
    if (table == NULL)
        return NULL_ERROR;

    if (table->size == 0)
        return EMPTY_ERROR;

    if (index < 0 || index >= table->size)
        return OUT_OF_BOUNDS;

    set_delete(table->cells[index]);
    table->cells[index] = NULL;

    for (int shift_index = index; shift_index < table->size - 1; shift_index++)
       table->cells[shift_index] = table->cells[shift_index + 1];

    table->cells[table->size - 1] = NULL;
    table->size--;

    if (table->size > 0 && table->size == table->capacity / 4)
        if (_table_resize(table, table->capacity / 2) != SUCCESS)
            return MEMORY_ERROR;

    return SUCCESS;
}

struct Set *get_entry(struct Table *table, int index) {
    if (table == NULL)
        return NULL;

    if (index < 0 || index >= table->size)
        return NULL;

    return table->cells[index];
}


void table_clear_entry(struct Table *table, int index) {
    set_delete(table->cells[index]);

    table->cells[index] = NULL;
}

void table_write_entry(struct Table *table, int index, struct Set *new_entry) {
    table_clear_entry(table, index);

    table->cells[index] = new_entry;
}
