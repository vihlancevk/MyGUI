#ifndef TOOL_BUTTON_HPP_
#define TOOL_BUTTON_HPP_

#include "AbstractButton.hpp"
#include "Tool.hpp"

class ToolButton: public AbstractButton {
    public:
        sf::Image image_;

        size_t size_ = 1;
        size_t curSize_ = 0;
        Tool** tool_;
    public:
        ToolButton(unsigned x, unsigned y, unsigned weight, unsigned hight, const char* image):
            AbstractButton(x, y, weight, hight),
            image_(),
            tool_((Tool**) new char[sizeof(Tool*)])
            {
                image_.loadFromFile(image);
            }
        ~ToolButton() {
            delete [] (char*) tool_;
        }

        ToolButton(const ToolButton& toolButton) = delete;
        ToolButton& operator = (const ToolButton& toolButton) = delete;

        size_t setTool(Tool* tool) {
            if (curSize_ >= size_) {
                std::cout << "Tool in ToolButton already set!\n";
                return 0;
            } else {
                tool_[curSize_++] = tool;
                return 1;
            }
        }

        void draw(sf::RenderWindow& window) override {
            sf::RectangleShape frame(sf::Vector2f((float) weight_ + 2 * outlineThickness_,
                                                  (float) hight_ + 2 * outlineThickness_));
            frame.setPosition(sf::Vector2f((float) (x_) - outlineThickness_,
                                           (float) (y_) - outlineThickness_));
            frame.setFillColor(sf::Color::White);
            frame.setOutlineThickness(outlineThickness_);
            frame.setOutlineColor(sf::Color::Black);

            sf::Texture texture;
            texture.loadFromImage(image_, sf::IntRect(0, 0, (int) weight_, (int) hight_));

            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition((float) x_, (float) y_);
            
            window.draw(frame);
            window.draw(sprite);

            if (isActive_) {
                const size_t pointRadius = 5;
                
                sf::CircleShape point(pointRadius);
                point.setPosition(sf::Vector2f((float) x_ + pointRadius, (float) y_ + pointRadius));
                point.setFillColor(sf::Color::Black);
            
                window.draw(point);
            }
        }
};

#endif // TOOL_BUTTON_HPP_
