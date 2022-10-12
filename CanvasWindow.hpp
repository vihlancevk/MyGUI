#ifndef CANVAS_WINDOW_HPP_
#define CANVAS_WINDOW_HPP_

#include "Widget.hpp"

class CanvasWindow: public Widget {
    public:
        unsigned x_;
        unsigned y_;

        unsigned weight_;
        unsigned hight_;
        
        const Color canvasColor_ = Color::WHITE;
        Color color_;
    public:
        CanvasWindow(unsigned x, unsigned y):
            x_(x),
            y_(y),
            weight_(1280),
            hight_(720),
            color_(Color::BLACK)
            {}
        ~CanvasWindow() {}

        void draw(sf::RenderWindow& window) override;
};

#endif // CANVAS_WINDOW_HPP_
