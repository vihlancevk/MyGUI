#include "Brush.hpp"

void Brush::draw(sf::RenderWindow& window) {
    sf::Texture texture;
    texture.loadFromImage(image_/*, sf::IntRect(0, 0, 160, 90)*/);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition((float) x_, (float) y_);
    
    window.draw(sprite);

    if (isActive_) {
        const size_t pointRadius = 5;
        
        sf::CircleShape point(pointRadius);
        point.setPosition(sf::Vector2f((float) x_ + pointRadius, (float) y_ + pointRadius));
        point.setFillColor(calculateColor(color_));
    
        window.draw(point);
    }

}
