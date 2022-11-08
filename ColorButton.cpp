#include "ColorButton.hpp"

void ColorButton::draw(sf::RenderWindow& window) {
    sf::RectangleShape colorButton(sf::Vector2f((float) (weight_) + 2 * outlineThickness_,
                                                (float) (hight_) + 2 * outlineThickness_));
    colorButton.setPosition(sf::Vector2f((float) (x_) - outlineThickness_,
                                        (float) (y_) - outlineThickness_));
    colorButton.setFillColor(color_);
    colorButton.setOutlineThickness(outlineThickness_);
    colorButton.setOutlineColor(sf::Color::Black);

    window.draw(colorButton);
    scrollBarButton_.draw(window);
}
