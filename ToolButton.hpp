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
        ToolButton(unsigned x, unsigned y, const char* image):
            AbstractButton(x, y),
            image_(),
            tool_((Tool**) new char[sizeof(Tool*)])
            {
                image_.loadFromFile(image);
            }
        ~ToolButton() {
            delete (char*) tool_;
        }

        // TODO: write a copy constructor and assignment operator
        ToolButton(const ToolButton& toolButton):
            AbstractButton(toolButton.x_, toolButton.y_),
            image_(toolButton.image_),
            tool_((Tool**) new char[sizeof(Tool*)])
            {
                tool_[curSize_++] = *toolButton.tool_;
            }
        ToolButton& operator = (const ToolButton& toolButton) {
            this->~AbstractButton();

            x_ = toolButton.x_;
            y_ = toolButton.y_;
            weight_ = toolButton.weight_;
            hight_ = toolButton.hight_;
            isActive_ = toolButton.isActive_;
            image_ = toolButton.image_;
            size_ = 1;
            curSize_ = 0;
            tool_ = (Tool**) new char[sizeof(Tool*)];
            tool_[curSize_++] = *toolButton.tool_;

            return *this;
        }

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
