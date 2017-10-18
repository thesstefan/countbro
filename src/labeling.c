#include <ctype.h>
#include "transform.h"
#include "set.h"
#include "labeling.h"

int *init_labels(int size) {
    int *labels = malloc(sizeof(int) * size);

    if (labels == NULL)
        return NULL;

    for (int index = 0; index < size; index++)
        labels[index] = 0;

    return labels;
}

struct Labels *init_label_list(struct binary_image *image) {
    struct Labels *new_label_list = malloc(sizeof(struct Labels));

    if (new_label_list == NULL)
        return NULL;

    new_label_list->height = image->height;
    new_label_list->width = image->width;

    new_label_list->matrix = init_labels(image->height * image->width);

    if (new_label_list->matrix == NULL)
        return NULL;

    return new_label_list;
}

int print_set(struct Set *set) {
    int count = 0;

    if (set == NULL)
        return -1;

    printf("SET : ");

    for (int index = 0; index < MAX_SETS && count <= set_cardinal(set); index++) 
        if (set_find(set, index) == 0) {
            printf("%d ", index);

            count++;
        }

    return 0;

    printf("\n");
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

int min(struct Set *neighbors) {
    if (set_cardinal(neighbors) != 0)
        for (int index = 1; index < MAX_LABELS; index++)
            if (set_find(neighbors, index) == 0)
                return index;

    return 0;
}

struct Labels *first_pass(struct binary_image *image, struct Set *set_list[MAX_SETS]) {
    int next_label = 1; 
    struct Labels *labels = init_label_list(image);

    if (labels == NULL)
        return NULL;

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK) {
                struct Set *neighbors = get_neighbors(labels, height, width);

                if (neighbors == NULL)
                    return NULL;

                if (set_cardinal(neighbors) == 0) {
                    set_list[next_label] = set_create();

                    *(labels->matrix + labels->width * height + width) = next_label;
 
                    next_label++;
                } else {
                    int label = min(neighbors);

                    //print_set(neighbors);

                    *(labels->matrix + labels->width * height + width) = label;

                    int count = 0;

                    for (int index = 1; index < next_label && count <= set_cardinal(neighbors); index++) {
                        if (set_find(neighbors, index) == 0) {
                            set_list[index] = set_union(set_list[index], neighbors); 
                        }
                    }

                    for (int set_index = 1; set_index < next_label; set_index++) {
                        for (int index = 1; index < next_label; index++)
                            if (set_find(set_list[index], set_index) == 0) {
                                set_list[index] = set_union(set_list[index], set_list[set_index]);
                                set_list[set_index] = set_union(set_list[index], set_list[set_index]);
                            }
                    }
                }
            }

    return labels;
}

int find_set_index(struct Set *set_list[MAX_SETS], int element) {
    for (int index = 1; index < MAX_SETS; index++)
        if (set_find(set_list[index], element) == 0)
            return index;

    return -1;
}

struct Labels *second_pass(struct binary_image *image, struct Labels *labels, struct Set *set_list[MAX_SETS]) {
//    for (int index = 1; print_set(set_list[index]) != -1; index++);

    struct Set *labels_set = set_create();

    for (int height = 0; height < image->height; height++)
        for (int width = 0; width < image->width; width++)
            if (*(image->matrix + image->width * height + width) != BLACK) {
                int my_label = find_set_index(set_list, *(labels->matrix + labels->width * height + width));

                set_add(labels_set, my_label);

                *(labels->matrix + labels->width * height + width) = my_label;
            }

    printf("NUMBER : %d\n", set_cardinal(labels_set));

    return labels;
}

struct Labels *labeling(struct binary_image *image) {
    if (image == NULL)
        return NULL;

    struct Set *set_list[MAX_SETS];

    struct Labels *temp_labels = first_pass(image, set_list);

    if (temp_labels == NULL)
        return NULL;

    struct Labels *labels = second_pass(image, temp_labels, set_list);

    return labels;
}
