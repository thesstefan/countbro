// @file This module provides a basic int set data type implementation

#ifndef SET_H
#define SET_H


struct Set {
    // add internal representation of a set
};

/**
 * @brief Create a new set
 * 
 * @return The new set.
 */
struct Set* set_create();

/**
 * @brief Delete a set
 * 
 * @param s The set to delete
 * 
 * @return none
 */
void set_delete(struct Set *s);


/**
 * @brief Add an element to a set
 * 
 * @param s The set to add to
 * @param x The element to add
 * 
 * @return 1 on success,
 *         0 on failure (e.g. the element already exists) - the set is not
 *         changed
 */
int set_add(struct Set *s, int x);

/**
 * @brief Remove an element from the set
 * 
 * @param s The set to remove from
 * @param x The element to remove
 * 
 * @return 1 on success,
 *         0 on failure (e.g. the element does not exist) - the set is not
 *         changed
 */
int set_remove(struct Set *s, int x);

/**
 * @brief Get the number of elements from a set
 * 
 * @param s The set
 *
 * @return The number of elements of the set s
 */
int set_cardinal(const struct Set *x);


/**
 * @brief Check if an element exists in a set
 * 
 * @param s The set to search in
 * @param x The element to look for
 * 
 * @return 1 if the element exists, 0 otherwise
 */
int set_find(const struct Set *s, int x);


/**
 * @brief Check if 2 sets are equal
 * 
 * @param a
 * @param b
 * 
 * @return 1 if the sets are equal, 0 otherwise
 */
int set_equals(const struct Set *a, const struct Set *b);

/**
 * @brief Perform the intersection of 2 sets
 * 
 * @param a
 * @param b
 * 
 * @return The intersection of a and b
 */
struct Set* set_intersection(const struct Set *a, const struct Set *b);

/**
 * @brief Perform the union of 2 sets
 * 
 * @param a
 * @param b
 * 
 * @return The union of a and b
 */
struct Set* set_union(const struct Set *a, const struct Set *b);

/**
 * @brief Perform the difference of 2 sets
 * 
 * @param a
 * @param b
 * 
 * @return The difference of a and b
 */
struct Set* set_difference(const struct Set *a, const struct Set *b);

#endif

