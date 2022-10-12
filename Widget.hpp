#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

enum Color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 4,
    WHITE = 7
};

class Widget {
    public:
        virtual ~Widget() = default;

        virtual void move() {}

        virtual void onMouseMove() {}
        virtual void onKeyboard() {}

        virtual void draw(sf::RenderWindow&) {
            std::cout << "Widget::draw()\n";
        }

        virtual void close() {}
};

#endif // WIDGET_HPP_