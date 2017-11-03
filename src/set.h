/**
 * @file set.h
 *
 * This module provides a basic int set data type implementation
*/

#include "errors.h"

#ifndef SET_H
#define SET_H

/** @brief Representation of a set */
struct Set {
/** @brief The Vector which repreents the Set */
    struct Vector *representation;
};

/**
 * @brief Create a new Set
 * 
 * @return Pointer to the new Set on success
 * @return `NULL` on failure (e.g. vector_create() failure)
 */
struct Set* set_create();

/**
 * @brief Delete a Set
 * 
 * @param set The Set to be deleted
 */
void set_delete(struct Set *set);

/**
 * @brief Add an element to a Set
 * 
 * @param set The Set to add to
 * @param item The element to add
 * 
 * @return @ref FAIL when vector_add() fails.
 * @return @ref SUCCESS on success.
 * @return @ref FOUND when @p item already is in @p set. The Set is not changed.
 * @return @ref NULL_ERROR when @p set or @p set->representation are `NULL`.
 * @return @ref FAIL when vector_add() fails.
 */
int set_add(struct Set *set, int item);

/**
 * @brief Remove an element from a Set
 * 
 * @param set The Set to remove from
 * @param item The element to remove
 * 
 * @return @ref SUCCESS on success
 * @return @ref NOT_FOUND when @p item is not in @p set. The Set is not changed.
 * @return @ref NULL_ERROR when @p set or @p set->representation are `NULL`
 * @return @ref EMPTY_ERROR when @p set is empty
 * @return @ref FAIL when vector_get() or vector_remove() fail 
 */
int set_remove(struct Set *set, int item);

/**
 * @brief Get the number of elements from a Set
 * 
 * @param set The Set to get the cardinal of
 *
 * @return Number of elements in @p set on success
 * @return @ref NULL_ERROR when @p set or @p set->representation are `NULL`
 */
int set_cardinal(struct Set *set);

/**
 * @brief Check if an element exists in a Set
 * 
 * @param set The Set to search in
 * @param item The element to look for
 * 
 * @return @ref FOUND if @p item is found in @p set
 * @return @ref NOT_FOUND if @p item is not found in @p set
 * @return @ref NULL_ERROR when @p set or @p set->representation are `NULL`
 * @return @ref FAIL when vector_get() fails
 */
int set_find(struct Set *set, int item);

/**
 * @brief Check if 2 sets are equal
 * 
 * @param a The first Set
 * @param b The second Set
 * 
 * @return @ref FOUND if the sets are equal (all elements of a are in b and viceversa)
 * @return @ref NOT_FOUND if the sets are not equal
 * @return @ref NULL_ERROR if @p a, @p b, @p a->representation or @p b->representation are `NULL`
 * @return @ref FAIL if vector_get() fails
 */
int set_equals(struct Set *a, struct Set *b);

/**
 * @brief Perform the intersection of 2 sets
 * 
 * @param a The first Set
 * @param b The second Set
 *
 * @return The intersection of @p a and @p b on success (`NULL` when empty)
 * @return `NULL` on fail (@p a, @p b, @p a->representation, @p b->representation are `NULL` or vector_get() / set_add() fail)
 */
struct Set* set_intersection(struct Set *a, struct Set *b);

/**
 * @brief Perform the union of 2 sets
 * 
 * @param a The first Set
 * @param b The second Set
 * 
 * @return The union of a and b on success (`NULL` when empty)
 * @return `NULL` on fail (@p a, @p b, @p a->representation, @p b->representation are `NULL` or vector_get() / set_add() fail)
 */
struct Set* set_union(struct Set *a, struct Set *b);

/**
 * @brief Perform the difference of 2 sets
 * 
 * @param a The first Set
 * @param b The second Set
 * 
 * @return The difference of a and b on success (`NULL` when empty)
 * @return `NULL` on fail (@p a, @p b, @p a->representation, @p b->representation are `NULL` or vector_get() / set_add() fail)
 */
struct Set* set_difference(struct Set *a, struct Set *b);

#endif

