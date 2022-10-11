#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Widget.hpp"

enum Color {
    RED = 1,
    GREEN = 2,
    BLUE = 4
};

class Button: Widget {
    public:
        unsigned x_;
        unsigned y_;

        unsigned weight_;
        unsigned hight_;

        Color color_;
        
        bool isClick_;
        bool isPress_;
    public:
        Button(unsigned x, unsigned y, Color color):
            x_(x),
            y_(y),
            weight_(160),
            hight_(90),
            color_(color),
            isClick_(false),
            isPress_(false)
            {}
        ~Button() {}

        void onClick();
        void onPress();

        void draw(sf::RenderWindow& window) override;
};

#endif // BUTTON_HPP_
