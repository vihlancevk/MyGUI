#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "AbstractButton.hpp"
#include "string.h"

class Button: public AbstractButton {
    public:
        sf::Font font_;
        unsigned size_ = 10;
        sf::Text text_;
    public:
        Button(unsigned x, unsigned y, unsigned weight, unsigned hight, const char* str):
            AbstractButton(x, y, weight, hight),
            font_(),
            text_()
            {
                font_.loadFromFile("./fonts/classic.ttf");
                new (&text_) sf::Text(str, font_, size_);
                text_.setFillColor(sf::Color::Black);
                text_.setPosition(sf::Vector2f((float) (x),
                                               (float) (y + hight / 2)));
            }
        ~Button() {}

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y))
                isActive_ = true;
        }

        void draw(sf::RenderWindow& window) override {
            sf::RectangleShape button(sf::Vector2f((float) (weight_),
                                                   (float) (hight_)));
            button.setPosition(sf::Vector2f((float) (x_),
                                            (float) (y_)));
            button.setFillColor(sf::Color::White);
            button.setOutlineThickness(outlineThickness_);
            button.setOutlineColor(sf::Color::Black);
            window.draw(button);

            window.draw(text_);
        }
};

#endif // BUTTON_HPP_
