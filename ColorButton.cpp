#include "ColorButton.hpp"

void ColorButton::draw(sf::RenderWindow& window) {
    sf::RectangleShape colorButton(sf::Vector2f((float) weight_, (float) hight_));
    colorButton.setPosition(sf::Vector2f((float) x_, (float) y_));
    colorButton.setFillColor(color_);

    window.draw(colorButton);
    scrollBarButton_.draw(window);
}
