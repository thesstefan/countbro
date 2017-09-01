#include <ctype.h>
#include "transform.h"
#include "set.h"
#include "labeling.h"

int *init_labels(int size) {
    int *labels = malloc(sizeof(int) * size);

    for (int index = 0; index < size; index++)
        labels[index] = 0;

    return labels;
}

struct Labels_list *init_label_list(struct binary_image *image) {
    struct Labels_list *new_label_list = malloc(sizeof(struct Labels_list));

    new_label_list->height = image->height;
    new_label_list->width = image->width;

    new_label_list->matrix = init_labels(image->height * image->width);

    return new_label_list;
}

struct Set *get_neighbors(struct Labels_list *labels, int y, int x) {
    struct Set *neighbors = set_create();

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

int min(struct Set *neighbors) {
    if (set_cardinal(neighbors) != 0)
        for (int index = 1; index < MAX_LABELS; index++)
            if (set_find(neighbors, index))
                return index;

    return 0;
}

struct Labels_list *first_pass(struct binary_image *image, struct Set *set_list[MAX_SETS]) {
    int next_label = 1; 
    struct Labels_list *labels = init_label_list(image);

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK) {
                struct Set *neighbors = get_neighbors(labels, height, width);

                if (set_cardinal(neighbors)) {
                    set_list[next_label] = set_create();

                    *(labels->matrix + labels->width * height + width) = next_label;
                   
                    next_label++;
                } else {
                    int label = min(neighbors);

                    *(labels->matrix + labels->width * height + width) = label;

                    int count = 0;

                    for (int index = 1; index < MAX_LABELS && count <= set_cardinal(neighbors); index++)
                        if (set_find(neighbors, index)) {
                            count++;

                            set_list[index] = set_union(set_list[index], neighbors); 
                        }
                }
            }

    return labels;
}

int find_set_index(struct Set *set_list[MAX_SETS], int element) {
    for (int index = 0; index < MAX_SETS; index++)
        if (set_find(set_list[index], element) == 1)
            return index;

    return -1;
}

struct Labels_list *second_pass(struct binary_image *image, struct Labels_list *labels, struct Set *set_list[MAX_SETS]) {
    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK)
                *(labels->matrix + labels->width * height + width) = find_set_index(set_list, *(labels->matrix + labels->width * height + width));

    return labels;
}

struct Labels_list *labeling(struct binary_image *image) {
    struct Set *set_list[MAX_SETS];

    struct Labels_list *temp_labels = first_pass(image, set_list);

    struct Labels_list *labels = second_pass(image, temp_labels, set_list);

    return labels;
}

