#include <ctype.h>

#include "table.h"
#include "transform.h"
#include "set.h"
#include "labeling.h"

int *init_labels_matrix(int size) {
    int *labels = malloc(sizeof(int) * size);

    if (labels == NULL)
        return NULL;

    for (int index = 0; index < size; index++)
        labels[index] = 0;

    return labels;
}

void delete_labels(struct Labels *labels) {
    if (labels != NULL)
        free(labels->matrix);

    free(labels);
}

struct Labels *init_labels(struct binary_image *image) {
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
            if (set_find(set, index) == 0)
                return index;

    return 0;
}

struct Labels *first_pass(struct binary_image *image, struct Table *table) {
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
                    table_add_entry(table, set_create());

                    *(labels->matrix + labels->width * height + width) = next_label;
 
                    next_label++;
                } else {
                    int label = set_min(neighbors);

                    *(labels->matrix + labels->width * height + width) = label;

                    int count = 0;

                    for (int index = 1; index < next_label && count <= set_cardinal(neighbors); index++)
                        if (set_find(neighbors, index) == 0)
                            table->cells[index] = set_union(table->cells[index], neighbors);

                    for (int set_index = 1; set_index < next_label; set_index++) {
                        for (int index = 1; index < next_label; index++)
                            if (set_find(table->cells[index], set_index) == 0) {
                                table->cells[index] = set_union(table->cells[index], table->cells[set_index]);

                                table->cells[set_index] = table->cells[index];
                            }
                    }

                    set_delete(neighbors);
                }
            }

    return labels;
}

int find_entry(struct Table *table, int element) {
    for (int index = 1; index < table->size; index++)
        if (set_find(table->cells[index], element) == 0)
            return index;

    return -1;
}

struct Labels *second_pass(struct binary_image *image, struct Labels *labels, struct Table *table) {
    struct Set *labels_set = set_create();
    
    table_print(table);

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK) {
                int label = find_entry(table, *(labels->matrix + labels->width * height + width));

                set_add(labels_set, label);

                *(labels->matrix + labels->width * height + width) = label;
            }

    printf("NUMBER : %d\n", set_cardinal(labels_set));

    return labels;
}

struct Labels *labeling(struct binary_image *image) {
    if (image == NULL)
        return NULL;

    struct Table *table = table_create();
    table_add_entry(table, set_create());

    struct Labels *temp_labels = first_pass(image, table);

    if (temp_labels == NULL)
        return NULL;

    struct Labels *labels = second_pass(image, temp_labels, table);

    delete_labels(temp_labels);

    return labels;
}
