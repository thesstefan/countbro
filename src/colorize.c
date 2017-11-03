#include "image.h"
#include "labelling.h"
#include "colorize.h"

const struct Pixel color[COLORS_NUMBER] = {{255, 0, 0}, // RED
                                           {0, 255, 0}, // LIME
                                           {0, 0, 255}, // BLUE
                                           {255, 0, 255}, // YELLOW
                                           {0, 255, 255}, // CYAN
                                           {255, 0, 255}, // MAGENTA
};

struct Pixel get_color(int number) {
    return color[number % COLORS_NUMBER];
}

void colorize(struct Image *image, struct Labels *labels) {
    for (int height = 0; height < labels->height; height++)
        for (int width = 0; width < labels->width; width++) {
            int label = *(labels->matrix + height * labels->width + width);

            if (label != 0)
                *(image->pixels + height * image->image_header.width + width) = get_color(label);
        }
}
