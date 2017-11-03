#include <ctype.h>

#include "set.h"
#include "table.h"

#include "transform.h"
#include "labelling.h"

#include "errors.h"

int *init_labels_matrix(int size) {
    int *labels = malloc(sizeof(int) * size);

    if (labels == NULL)
        return NULL;

    for (int index = 0; index < size; index++)
        labels[index] = 0;

    return labels;
}

void delete_labels(struct Labels *labels) {
    if (labels != NULL) {
        free(labels->matrix);

        labels->matrix = NULL;
    }

    free(labels);

    labels = NULL;
}

struct Labels *init_labels(struct Binary *image) {
    struct Labels *new_labels = malloc(sizeof(struct Labels));

    if (new_labels == NULL)
        return NULL;

    new_labels->height = image->height;
    new_labels->width = image->width;

    new_labels->matrix = init_labels_matrix(image->height * image->width);

    if (new_labels->matrix == NULL) {
        delete_labels(new_labels);

        return NULL;
    }

    return new_labels;
}

struct Set *get_neighbors(struct Labels *labels, int y, int x) {
    struct Set *neighbors = set_create();

    if (neighbors == NULL)
        return NULL;

    if (x - 1 >= 0)
        set_add(neighbors, *(labels->matrix + labels->width * y + (x - 1)));

    if (y - 1 >= 0)
        set_add(neighbors, *(labels->matrix + labels->width * (y - 1) + x));

#ifdef CONNECTIVITY_8
    if (y - 1 >= 0 && x - 1 >= 0)
        set_add(neighbors, *(labels->matrix + labels->width * (y - 1) + (x - 1)));
#endif

    set_remove(neighbors, 0);

    return neighbors;
}

int set_min(struct Set *set) {
    if (set_cardinal(set) != 0)
        for (int index = 0; index < MAX_LABELS; index++)
            if (set_find(set, index) == FOUND)
                return index;

    return 0;
}

struct Labels *first_pass(struct Binary *image, struct Table *table) {
    int next_label = 1; 
    struct Labels *labels = init_labels(image);

    if (labels == NULL)
        return NULL;

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK) {
                struct Set *neighbors = get_neighbors(labels, height, width);

                if (neighbors == NULL)
                    return NULL;

                if (set_cardinal(neighbors) == 0) {
                    struct Set *new_entry = set_create();

                    set_add(new_entry, next_label);

                    table_add_entry(table, new_entry);

                    *(labels->matrix + labels->width * height + width) = next_label;
 
                    next_label++;
                } else {
                    int label = set_min(neighbors);

                    *(labels->matrix + labels->width * height + width) = label;

                    int count = 0;

                    for (int index = 1; index < next_label && count < set_cardinal(neighbors); index++)
                        if (set_find(neighbors, index) == FOUND) {
                            struct Set *entry = set_union(get_entry(table, index), neighbors);

//                            table_clear_entry(table, index);

                            table_write_entry(table, index, entry);

                            count++;

                        }

                    set_delete(neighbors);
                }
            }


// TO DO : FIND A BETTER WAY
                    for (int set_index = 1; set_index < next_label; set_index++) {
                        for (int index = 1; index < next_label; index++)
                            if (set_find(get_entry(table, index), set_index) == FOUND) {
                                struct Set *entry = set_union(get_entry(table, index), get_entry(table, set_index));

//                                table_clear_entry(table, index);

                                table_write_entry(table, index, entry);
                            }
                    }
    
    return labels;
}

int find_entry(struct Table *table, int element) {
    for (int index = 1; index < table->size; index++)
        if (set_find(table->cells[index], element) == FOUND)
            return index;

    return -1;
}

// TO DO : Find a way to return the unique labels set, while respecting SRP
int second_pass(struct Binary *image, struct Labels *labels, struct Table *table) {
    struct Set *unique_labels = set_create();
    
    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK) {
                int label = find_entry(table, *(labels->matrix + labels->width * height + width));

                set_add(unique_labels, label);

                *(labels->matrix + labels->width * height + width) = label;
            }

    int labels_count = set_cardinal(unique_labels);

    set_delete(unique_labels);

    return labels_count;
}

struct Labels *labelling(struct Binary *image) {
    if (image == NULL)
        return NULL;

    struct Table *table = table_create();
    table_add_entry(table, set_create());

    struct Labels *labels = first_pass(image, table);

    if (labels == NULL)
        return NULL;

// TO DO : HANDLE BETTER
    int count = second_pass(image, labels, table);

    printf("COUNT : %d\n", count);

    table_delete(table);

    return labels;
}
