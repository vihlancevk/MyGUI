#include "Button.hpp"

void Button::draw(sf::RenderWindow& window) {
    sf::RectangleShape button(sf::Vector2f((float) weight_, (float) hight_));
    button.setPosition(sf::Vector2f((float) x_, (float) y_));
    button.setFillColor(calculateColor(color_));

    window.draw(button);

    if (isActive_) {
        const size_t pointRadius = 5;
        
        sf::CircleShape point(pointRadius);
        point.setPosition(sf::Vector2f((float) x_ + pointRadius, (float) y_ + pointRadius));
        point.setFillColor(calculateColor(Color::BLACK));
    
        window.draw(point);
    }
}
