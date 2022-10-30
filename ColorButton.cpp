#include "ColorButton.hpp"

void ColorButton::draw(sf::RenderWindow& window) {
    sf::RectangleShape colorButton(sf::Vector2f((float) weight_, (float) hight_));
    colorButton.setPosition(sf::Vector2f((float) x_, (float) y_));
    colorButton.setFillColor(calculateColor(color_));

    window.draw(colorButton);

    if (isActive_) {
        const size_t pointRadius = 5;
        
        sf::CircleShape point(pointRadius);
        point.setPosition(sf::Vector2f((float) x_ + pointRadius, (float) y_ + pointRadius));
        point.setFillColor(calculateColor(Color::BLACK));
    
        window.draw(point);
    }
}
