#ifndef BRUSH_HPP_
#define BRUSH_HPP_

#include <SFML/Graphics.hpp>
#include "../plugin.h"

class Brush: public ITool {
    public:
        unsigned size_;
        sf::Color color_;
    public:
        Brush(unsigned size = 10, sf::Color color = sf::Color::Black):
            size_(size),
            color_(color)
            {}

        ~Brush() {}

        void apply(unsigned int* pixmap, int width, int height, Pair<int> point) override {
            int startX = 0;
            if ((unsigned) point.x > size_ && (unsigned) (width - point.x) > size_) {
                startX = point.x - (int) size_;
            } else if (width - point.x <= (int) size_) {
                startX = width - (int) size_;
            }

            int startY = 0;
            if ((unsigned) point.y > size_ && unsigned (height - point.y) > size_) {
                startY = point.y - (int) size_;
            } else if (height - point.y <= (int) size_) {
                startY = height - (int) size_;
            }

            for (int i = startY; i < startY + (int) size_; i++) {
                for (int j = 4 * startX; j < 4 * (startX + (int) size_); j += 4) {
                    pixmap[i * 4 * width + j] = color_.r;
                    pixmap[i * 4 * width + j + 1] = color_.g;
                    pixmap[i * 4 * width + j + 2] = color_.b;
                    pixmap[i * 4 * width + j + 3] = color_.a;
                }
            }
        }

        void deactivate() override {}
};

#endif // BRUSH_HPP_
