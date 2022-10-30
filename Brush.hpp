#ifndef BRUSH_HPP_
#define BRUSH_HPP_

sf::Color calculateColor(Color color);

#include "Tool.hpp"

class Brush: public Tool {
    public:
        Color color_;
        unsigned size_;
    public:
        Brush():
            Tool(),
            color_(Color::BLACK),
            size_(10)
            {}

        ~Brush() {}

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
                    pixels[startPixel + i * canvasWeight + j].color = calculateColor(color_);
                }
            }
        }
};

sf::Color calculateColor(Color color) {
    sf::Color sfColor
    (
        (sf::Uint8) ((color & 1) * 255),
        (sf::Uint8) (((color & 2) >> 1) * 255),
        (sf::Uint8) (((color & 4) >> 2) * 255)
    );

    return sfColor;
}

#endif // BRUSH_HPP_
