#include <studio.h>

#define TABLE_INIT_CAPACITY 4

struct Table {
    int size;
    int capacity;

    struct Set **cells;
}

struct Table *table_create() {
    struct Table *new_table = malloc(sizeof(struct Table));

    if (new_table == NULL)
        return NULL;

    new_table->size = 0;
    new_table->capacity = TABLE_INIT_CAPACITY;

    new_table->cells = malloc(sizeof(struct Set *) * TABLE_INIT_CAPACITY);

    if (new_table->cells == NULL)
        return NULL;

    for (int index = 0; index < TABLE_INIT_CAPACITY; index++)
        new_table->cells[index] = malloc(sizeof(struct Set));

    return new_table;
}

int table_resize(struct Table *table, int capacity) {
    struct Set **cells = realloc(table->cells, sizeof(struct Set *) * new_capacity);

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

void table_remove(struct Table *table) {
    if (table != NULL) {
        if (table->cells != NULL) {
            for (int index = 0; index < table->size; index++)
                free(cells[index]);
        }

        free(table->cells);
    }

    free(table);
}
