#ifndef COLOR_BUTTON_HPP_
#define COLOR_BUTTON_HPP_

#include "Color.hpp"
#include "AbstractButton.hpp"

class ColorButton: public AbstractButton {
    public:
        Color color_;
    public:
        ColorButton():
            AbstractButton(0, 0),
            color_(WHITE)
            {}

        ColorButton(unsigned x, unsigned y, Color color):
            AbstractButton(x, y),
            color_(color)
            {}
        ~ColorButton() {}

        void draw(sf::RenderWindow& window) override;
};

#endif // COLOR_BUTTON_HPP_
