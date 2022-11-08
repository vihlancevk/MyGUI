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

        void onMouseMove(unsigned x, unsigned y) override {
            scrollBarButton_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) override {
            scrollBarButton_.onMouseClick(x, y);
        }

        void onMouseReleased(unsigned x, unsigned y) override {
            scrollBarButton_.onMouseReleased(x, y);

            size_ = scrollBarButton_.calculateValue();
        }

        void draw(sf::RenderWindow& window) override {
            sf::RectangleShape sizeButton(sf::Vector2f((float) (weight_) + 2 * outlineThickness_,
                                                       (float) (hight_) + 2 * outlineThickness_));
            sizeButton.setPosition(sf::Vector2f((float) (x_) - outlineThickness_,
                                                (float) (y_) - outlineThickness_));
            sizeButton.setFillColor(sf::Color::White);
            sizeButton.setOutlineThickness(outlineThickness_);
            sizeButton.setOutlineColor(sf::Color::Black);

            window.draw(sizeButton);
            scrollBarButton_.draw(window);
        }
};

#endif // SIZE_BUTTON_HPP_
