#ifndef ERASER_HPP_
#define ERASER_HPP_

#include "Tool.hpp"

class Eraser: public Tool {
    public:
        Eraser(unsigned x, unsigned y, const char* image):
            Tool(x, y, image)
            {}
        ~Eraser() {}

        void actionWithCanvas(sf::VertexArray& pixels,
                              unsigned canvasX, unsigned canvasY, unsigned canvasWeight, unsigned canvasHight,
                              unsigned x, unsigned y) override {
            unsigned startX = 0;
            if (x - canvasX > size_ && (canvasX + canvasWeight) - x > size_) {
                startX = x - canvasX - size_;
            } else if ((canvasX + canvasWeight) - x <= size_) {
                startX = canvasWeight - 2*size_;
            }

            unsigned startY = 0;
            if (y - canvasY > size_ && (canvasY + canvasHight) - y > size_) {
                startY = y - canvasY - size_;
            } else if ((canvasY + canvasHight) - y <= size_) {
                startY = canvasHight - 2*size_;
            }

            unsigned startPixel = (startY) * canvasWeight + (startX);
        
            for (unsigned i = 0; i < 2*size_; i++) {
                for (unsigned j = 0; j < 2*size_; j++) {
                    pixels[startPixel + i * canvasWeight + j].color = calculateColor(Color::WHITE);
                }
            }

        }

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y)) {
                isActive_ = (isActive_) ? false : true;
            }
        }

        void draw(sf::RenderWindow& window) override;
};

#endif // ERASER_HPP_
