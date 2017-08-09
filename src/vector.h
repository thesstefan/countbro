#define VECTOR_INIT_CAPACITY 4

struct Vector {
    int *items;
    int capacity;
    int count;
}

struct Vector *vector_create();
struct Vector *vector_resize(struct Vector *vector, int capacity);
void vector_add(struct Vector *vector, int item);
void vector_set(struct Vector *vector, int index, int item);
void vector_get(struct Vector *vector, int index);
void vector_delete(struct Vector *vector, int index);
void vector_free(struct Vector *vector);
