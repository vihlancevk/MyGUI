#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Widget {
    public:
        unsigned x_, y_;

        unsigned weight_, hight_;

        float outlineThickness_ = 3;
    public:
        Widget(unsigned x, unsigned y, unsigned weight, unsigned hight):
            x_(x),
            y_(y),
            weight_(weight),
            hight_(hight)
            {}

        virtual bool isPointInWidget(unsigned x, unsigned y) {
            if (x_ <= x && x <= (x_ + weight_)) {
                if (y_ <= y && y <= (y_ + hight_)) {
                    return true;
                }
            }

            return false;
        }

        virtual void move() {}

        virtual void onMouseMove(unsigned, unsigned) {}

        virtual void onMouseClick(unsigned, unsigned) {}
        
        virtual void onMouseReleased(unsigned, unsigned) {}
        
        virtual void onKeyboard(int) {}

        virtual void draw(sf::RenderWindow&) {}

        virtual void close() {}

        virtual ~Widget() = default;
};

#endif // WIDGET_HPP_
