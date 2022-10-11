#include "Button.hpp"

void Button::draw(sf::RenderWindow& window) {
    sf::RectangleShape button(sf::Vector2f((float) weight_, (float) hight_));
    
    button.setPosition(sf::Vector2f((float) x_, (float) y_));

    button.setFillColor(sf::Color((sf::Uint8) ((color_ & 1) * 255),
                                  (sf::Uint8) (((color_ & 2) >> 1) * 255),
                                  (sf::Uint8) (((color_ & 4) >> 2) * 255)));

    window.draw(button);
}
