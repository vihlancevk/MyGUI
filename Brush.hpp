#ifndef BRUSH_HPP_
#define BRUSH_HPP_

#include "Tool.hpp"

class Brush: public Tool {
    public:
        Brush():
            Tool()
            {}

        ~Brush() {}

        void actionWithCanvas(sf::VertexArray& pixels,
                              unsigned canvasX, unsigned canvasY, unsigned canvasWeight, unsigned canvasHight,
                              unsigned x, unsigned y) override {
            unsigned startX = 0;
            if (x - canvasX > size_ && (canvasX + canvasWeight) - x > size_) {
                startX = x - canvasX - size_;
            } else if ((canvasX + canvasWeight) - x <= size_) {
                startX = canvasWeight - size_;
            }

            unsigned startY = 0;
            if (y - canvasY > size_ && (canvasY + canvasHight) - y > size_) {
                startY = y - canvasY - size_;
            } else if ((canvasY + canvasHight) - y <= size_) {
                startY = canvasHight - size_;
            }

            unsigned startPixel = (startY) * canvasWeight + (startX);

            for (unsigned i = 0; i < size_; i++) {
                for (unsigned j = 0; j < size_; j++) {
                    pixels[startPixel + i * canvasWeight + j].color = color_;
                }
            }
        }
};

#endif // BRUSH_HPP_
