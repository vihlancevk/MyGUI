#ifndef COLOR_BUTTON_HPP_
#define COLOR_BUTTON_HPP_

#include "AbstractButton.hpp"
#include "ScrollBarButton.hpp"

class ColorButton: public AbstractButton {
    public:
        sf::Color color_;

        ScrollBarButton scrollBarButton_;
    public:
        ColorButton():
            AbstractButton(0, 0),
            color_(sf::Color::White),
            scrollBarButton_(ScrollBarButton(0, 0, 0, 255))
            {}

        ColorButton(unsigned x, unsigned y, sf::Color color):
            AbstractButton(x, y),
            color_(color),
            scrollBarButton_(ScrollBarButton(x, y, 0, 255))
            {}
        ~ColorButton() {}

        void onMouseMove(unsigned x, unsigned y) override {
            scrollBarButton_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) override {
            scrollBarButton_.onMouseClick(x, y);
        }

        void onMouseReleased(unsigned x, unsigned y) override {
            scrollBarButton_.onMouseReleased(x, y);
        }

        void draw(sf::RenderWindow& window) override;
};

#endif // COLOR_BUTTON_HPP_
