/**
 * @file table.h
 *
 * This module provides a basic "table" data type implementation
 *
 * A table is represented as an bidimensional array of multiple Set structures
 */

#include <stdlib.h>

#include "vector.h"
#include "set.h"

#ifndef TABLE_H
#define TABLE_H

/** @brief Macro used for the initial capacity of a Table */
#define TABLE_INIT_CAPACITY 4

/** @brief Representation of a table */
struct Table {
/** @brief Cells of the Table (Set s) */
    struct Set **cells;
/** @brief Capacity of the Table */
    int capacity;
/** @brief Size of the Table */
    int size;
};

/**
 * @brief Create a new Table
 *
 * @return Pointer to new Table on success
 * @return `NULL` on failure (e.g. failed `malloc()`)
 */
struct Table *table_create();

/** 
 * @brief Delete a Table
 *
 * @param table The Table to be deleted
 */
void table_delete(struct Table *table);

/** 
 * @brief Add a Set to the Table
 *
 * @param table The Table to add to
 * @param set The Set to add  
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR if @p table or @p set are `NULL`
 * @return @ref MEMORY_ERROR if `realloc()` fails
 */
int table_add_entry(struct Table *table, struct Set *set);

/**
 * @brief Remove a Set from the Table, given the index
 *
 * @param table The Table to delete from
 * @param index The index of the Table to be deleted
 *
 * @return @ref SUCCESS on success
 * @return @ref NULL_ERROR if @p table is `NULL`
 * @return @ref MEMORY_ERROR if `realloc()` fails
 * @return @ref OUT_OF_BOUNDS if @p index is out of bounds
 * @return @ref EMPTY_ERROR if @p table is empty
 */
int table_remove_entry(struct Table *table, int index);

/**
 * @brief Get a Set from the Table, given the index
 *
 * @param table The Table to get the Set from
 * @param index The index of the Set to get
 *
 * @return Pointer to the Set on success
 * @return `NULL` on fail (@p table is `NULL` or @p index is out of bounds)
 */
struct Set *get_entry(struct Table *table, int index);

/**
 * @brief Delete a Set of the Table, given the index
 *
 * @param table The Table to delete from
 * @param index The index of the Set to be deleted
 */
void table_clear_entry(struct Table *table, int index);

/**
 * @brief Replace a Set of the Table, with another, given the index and the new Set (table_clear_entry() is used first).
 *
 * @param table The Table to change from
 * @param index The index of the Set to be changed
 * @param new_entry The new Set
 */
void table_write_entry(struct Table *table, int index, struct Set *new_entry);

#endif
