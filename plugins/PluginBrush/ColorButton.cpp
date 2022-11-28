#include "ColorButton.hpp"

void ColorButton::draw(unsigned int* screen, int width, int height) {
    // (*) --------------------
    //     |                  |
    //     |                  |
    //     |                  |
    //     --------------------
    for (unsigned j = (y_ - outlineThickness_); j < y_; j++) {
        for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
            screen[j * 4 * (unsigned) width + i] =
            screen[j * 4 * (unsigned) width + i + 1] =
            screen[j * 4 * (unsigned) width + i + 2] = 0;
            screen[j * 4 * (unsigned) width + i + 3] = 255;
        }
    }
    
    //     --------------------
    //     |                  |
    //     |                  |
    //     |                  |
    // (*) --------------------
    for (unsigned j = (y_ + hight_); j < (y_ + hight_ + outlineThickness_); j++) {
        for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
            screen[j * 4 * (unsigned) width + i] =
            screen[j * 4 * (unsigned) width + i + 1] =
            screen[j * 4 * (unsigned) width + i + 2] = 0;
            screen[j * 4 * (unsigned) width + i + 3] = 255;
        }
    }
    
    // (*)
    //  --------------------
    //  |                  |
    //  |                  |
    //  |                  |
    //  --------------------
    for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
        for (unsigned i = 4 * (x_ - outlineThickness_); i < 4 * (x_) - (4 - 1); i += 4) {
            screen[j * 4 * (unsigned) width + i] =
            screen[j * 4 * (unsigned) width + i + 1] =
            screen[j * 4 * (unsigned) width + i + 2] = 0;
            screen[j * 4 * (unsigned) width + i + 3] = 255;
        }
    }

    //                    (*)
    //  --------------------
    //  |                  |
    //  |                  |
    //  |                  |
    //  --------------------
    for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
        for (unsigned i = 4 * (x_ + weight_); i < 4 * (x_ + weight_ + outlineThickness_) - (4 - 1); i += 4) {
            screen[j * 4 * (unsigned) width + i] =
            screen[j * 4 * (unsigned) width + i + 1] =
            screen[j * 4 * (unsigned) width + i + 2] = 0;
            screen[j * 4 * (unsigned) width + i + 3] = 255;
        }
    }

    for (unsigned j = y_; j < (y_ + hight_); j++) {
        for (unsigned i = 4 * (x_); i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
            screen[j * 4 * (unsigned) width + i] = color_.r;
            screen[j * 4 * (unsigned) width + i + 1] = color_.g;
            screen[j * 4 * (unsigned) width + i + 2] = color_.b;
            screen[j * 4 * (unsigned) width + i + 3] = color_.a;
        }
    }

    scrollBarButton_.draw(screen, width, height);
}
