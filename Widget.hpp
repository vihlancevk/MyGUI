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
        unsigned x_, y_;

        unsigned weight_, hight_;
    public:
        Widget():
            x_(0),
            y_(0),
            weight_(0),
            hight_(0)
            {}

        Widget(unsigned x, unsigned y, unsigned weight, unsigned hight):
            x_(x),
            y_(y),
            weight_(weight),
            hight_(hight)
            {}

        sf::Color calculateColor(Color color) {
            sf::Color sfColor
            (
                (sf::Uint8) ((color & 1) * 255),
                (sf::Uint8) (((color & 2) >> 1) * 255),
                (sf::Uint8) (((color & 4) >> 2) * 255)
            );

            return sfColor;
        }

        bool isPointInWidget(unsigned x, unsigned y) {
            if (x_ <= x && x <= (x_ + weight_)) {
                if (y_ <= y && y <= (y_ + hight_)) {
                    return true;
                }
            }

            return false;
        }

        virtual void move() {}

        virtual void onMouseMove() {}
        virtual void onMouseClick(unsigned, unsigned) {
            std::cout << "In Widget::onMouseClick()\n";
        }
        virtual void onKeyboard() {}

        virtual void draw(sf::RenderWindow&) {}

        virtual void close() {}

        virtual ~Widget() = default;
};

#endif // WIDGET_HPP_