#ifndef COLOR_BUTTON_HPP_
#define COLOR_BUTTON_HPP_

#include "../AbstractButton.hpp"
#include "../ScrollBarButton.hpp"

class ColorButton: public AbstractButton {
    public:
        sf::Color color_;

        ScrollBarButton scrollBarButton_;
    public:
        ColorButton(unsigned x, unsigned y, unsigned weight, unsigned hight, sf::Color color):
            AbstractButton(x, y, weight, hight),
            color_(color),
            scrollBarButton_(ScrollBarButton(x, y, weight, hight, 0, 255))
            {}
        ~ColorButton() {}

        void on_mouse_press(Pair<int> point) override {
            scrollBarButton_.on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) override {
            scrollBarButton_.on_mouse_release(point);
        }

        void on_mouse_move(Pair<int> point) override {
            scrollBarButton_.on_mouse_move(point);
        }

        void draw(unsigned int* screen, int width, int height) override;
};

#endif // COLOR_BUTTON_HPP_
