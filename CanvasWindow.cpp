#include "CanvasWindow.hpp"

void CanvasWindow::draw(sf::RenderWindow& window) {
    window.draw(pixels_);

    if (isActive_) {
        const size_t pointRadius = 5;
        
        sf::CircleShape point(pointRadius);
        point.setPosition(sf::Vector2f((float) x_ + pointRadius, (float) y_ + pointRadius));
        point.setFillColor(calculateColor(paintbrushColor_));
    
        window.draw(point);
    }
}
