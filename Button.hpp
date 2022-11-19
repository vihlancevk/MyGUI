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

        void on_mouse_press(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                isActive_ = true;
                isContains_ = false;
            }
        }

        void draw(unsigned int* /*screen*/, int /*width*/, int /*height*/) override {
            // sf::RectangleShape button(sf::Vector2f((float) (weight_),
            //                                        (float) (hight_)));
            // button.setPosition(sf::Vector2f((float) (x_),
            //                                 (float) (y_)));
            // button.setFillColor(sf::Color::White);
            // button.setOutlineThickness(outlineThickness_);
            // button.setOutlineColor(sf::Color::Black);
            // window.draw(button);

            // window.draw(text_);

            std::cout << "Button::draw(unsigned int*, int, int)\n";
        }
};

#endif // BUTTON_HPP_
