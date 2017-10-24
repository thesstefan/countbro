#if defined(CONNECTIVITY_8)
    #define NEEDED_NEIGHBORS 3
#elif defined(CONNECTIVITY_4)
    #define NEEDED_NEIGHBORS 2
#else
    #define CONNECTIVITY_8
    #define NEEDED_NEIGHBORS 3
#endif

#define MAX_LABELS 1000000
#define MAX_SETS 1000

struct Labels {
    int height;
    int width;

    int *matrix;
};

struct Labels *labeling(struct binary_image *image);
void delete_labels(struct Labels *labels);
