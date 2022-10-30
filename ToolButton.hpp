#ifndef TOOL_BUTTON_HPP_
#define TOOL_BUTTON_HPP_

#include "AbstractButton.hpp"
#include "Tool.hpp"

class ToolButton: public AbstractButton {
    public:
        sf::Image image_;

        Tool* tool_;
    public:
        ToolButton(unsigned x, unsigned y, const char* image, Tool* tool):
            AbstractButton(x, y),
            image_(),
            tool_(tool)
            {
                image_.loadFromFile(image);
            }
        ~ToolButton() {}

        // One toolButton - one tool
        ToolButton(const ToolButton& toolButton) = delete;
        ToolButton& operator = (const ToolButton& toolButton) = delete;

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

#endif // TOOL_BUTTON_HPP_
