#ifndef ERASER_HPP_
#define ERASER_HPP_

#include "plugin.h"

class Eraser: public ITool {
    public:
        unsigned size_;
        sf::Color color_;
    public:
        Eraser(unsigned size = 10, sf::Color color = sf::Color::Black):
            size_(size),
            color_(color)
            {}

        ~Eraser() {}

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
                    pixmap[i * 4 * width + j] = 255;
                    pixmap[i * 4 * width + j + 1] = 255;
                    pixmap[i * 4 * width + j + 2] = 255;
                    pixmap[i * 4 * width + j + 3] = 255;
                }
            }
        }

        void deactivate() override {}
};

#endif // ERASER_HPP_
