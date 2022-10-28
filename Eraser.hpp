#ifndef ERASER_HPP_
#define ERASER_HPP_

#include "Tool.hpp"

class Eraser: public Tool {
    private:
        unsigned multiplierForSize_ = 2;
    public:
        Eraser(unsigned x, unsigned y, const char* image):
            Tool(x, y, image)
            {}
        ~Eraser() {}

        void actionWithCanvas(sf::VertexArray& pixels,
                              unsigned canvasX, unsigned canvasY, unsigned canvasWeight, unsigned canvasHight,
                              unsigned x, unsigned y) override {
            unsigned size = size_ * multiplierForSize_;
            
            unsigned startX = 0;
            if (x - canvasX > size && (canvasX + canvasWeight) - x > size) {
                startX = x - canvasX - size;
            } else if ((canvasX + canvasWeight) - x <= size) {
                startX = canvasWeight - 2*size;
            }

            unsigned startY = 0;
            if (y - canvasY > size && (canvasY + canvasHight) - y > size) {
                startY = y - canvasY - size;
            } else if ((canvasY + canvasHight) - y <= size) {
                startY = canvasHight - 2*size;
            }

            unsigned startPixel = (startY) * canvasWeight + (startX);
        
            for (unsigned i = 0; i < 2*size; i++) {
                for (unsigned j = 0; j < 2*size; j++) {
                    pixels[startPixel + i * canvasWeight + j].color = calculateColor(Color::WHITE);
                }
            }

        }

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y)) {
                isActive_ = (isActive_) ? false : true;
            }
        }

        void draw(sf::RenderWindow& window) override {
            sf::Texture texture;
            texture.loadFromImage(image_/*, sf::IntRect(0, 0, 160, 90)*/);

            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition((float) x_, (float) y_);
    
            window.draw(sprite);

            if (isActive_) {
                const size_t pointRadius = 5;
                
                sf::CircleShape point(pointRadius);
                point.setPosition(sf::Vector2f((float) x_ + pointRadius, (float) y_ + pointRadius));
                point.setFillColor(calculateColor(Color::BLACK));
            
                window.draw(point);
            }
        }
};

#endif // ERASER_HPP_
