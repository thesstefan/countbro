#if defined(CONNECTIVITY_8)
    #define NEEDED_NEIGHBORS 3
#elif defined(CONNECTIVITY_4)
    #define NEEDED_NEIGHBORS 2
#else
    #define CONNECTIVITY_8
    #define NEEDED_NEIGHBORS 3
#endif

#define MAX_LABELS 100
#define MAX_SETS 100

struct Labels_list {
    int height;
    int width;

    int *matrix;
};

struct Labels_list *labeling(struct binary_image *image);
