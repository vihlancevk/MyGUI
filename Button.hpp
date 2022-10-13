#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "AbstractButton.hpp"

class Button: public AbstractButton {
    public:
        Color color_;
    public:
        Button():
            AbstractButton(0, 0),
            color_(WHITE)
            {}

        Button(unsigned x, unsigned y, Color color):
            AbstractButton(x, y),
            color_(color)
            {}
        ~Button() {}

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y))
                isActive_ = (isActive_) ? false : true;       
        }

        void draw(sf::RenderWindow& window) override;
};

#endif // BUTTON_HPP_
