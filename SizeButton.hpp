#ifndef SIZE_BUTTON_HPP_
#define SIZE_BUTTON_HPP_

#include "AbstractButton.hpp"
#include "ScrollBarButton.hpp"

class SizeButton: public AbstractButton {
    public:
        unsigned size_ = 10;

        ScrollBarButton scrollBarButton_;
    public:
        SizeButton(unsigned x, unsigned y, unsigned weight, unsigned hight):
            AbstractButton(x, y, weight, hight),
            scrollBarButton_(ScrollBarButton(x, y, weight, hight, 5, 25))
            {}
        ~SizeButton() {}

        void on_mouse_press(Pair<int> point) override {
            scrollBarButton_.on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) override {
            scrollBarButton_.on_mouse_release(point);
        }

        void on_mouse_move(Pair<int> point) override {
            scrollBarButton_.on_mouse_move(point);
        }

        void draw(unsigned int* screen, int width, int height) override {
            // sf::RectangleShape sizeButton(sf::Vector2f((float) (weight_),
            //                                            (float) (hight_)));
            // sizeButton.setPosition(sf::Vector2f((float) (x_),
            //                                     (float) (y_)));
            // sizeButton.setFillColor(sf::Color::White);
            // sizeButton.setOutlineThickness(outlineThickness_);
            // sizeButton.setOutlineColor(sf::Color::Black);

            // window.draw(sizeButton);

            std::cout << "SizeButton::draw(unsigned int*, int, int)\n";

            scrollBarButton_.draw(screen, width, height);
        }
};

#endif // SIZE_BUTTON_HPP_
