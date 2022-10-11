#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Widget {
    public:
        virtual ~Widget() = default;

        virtual void move() {}

        virtual void onMouseMove() {}
        virtual void onKeyboard() {}

        virtual void draw(sf::RenderWindow& window) {}

        virtual void close() {}
};

#endif // WIDGET_HPP_