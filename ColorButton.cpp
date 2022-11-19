#include "ColorButton.hpp"

void ColorButton::draw(unsigned int* screen, int width, int height) {
    // sf::RectangleShape colorButton(sf::Vector2f((float) (weight_) + 2 * outlineThickness_,
    //                                             (float) (hight_) + 2 * outlineThickness_));
    // colorButton.setPosition(sf::Vector2f((float) (x_) - outlineThickness_,
    //                                     (float) (y_) - outlineThickness_));
    // colorButton.setFillColor(color_);
    // colorButton.setOutlineThickness(outlineThickness_);
    // colorButton.setOutlineColor(sf::Color::Black);

    // window.draw(colorButton);

    std::cout << "ColorButton::draw(unsigned int*, int, int)\n";

    scrollBarButton_.draw(screen, width, height);
}
