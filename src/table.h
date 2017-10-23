#include <stdlib.h>

#include "vector.h"
#include "set.h"

#define TABLE_INIT_CAPACITY 4

struct Table {
    int size;
    int capacity;

    struct Set **cells;
};

struct Table *table_create();
int table_resize(struct Table *table, int capacity);
int table_add_entry(struct Table *table, struct Set *set);
void table_delete(struct Table *table);
void table_print(struct Table *table);
void table_clear_entry(struct Table *table, int index);
void table_write_entry(struct Table *table, int index, struct Set *new_entry);
int table_remove_entry(struct Table *table, int index);
struct Set *get_entry(struct Table *table, int index);
