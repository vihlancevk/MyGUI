#ifndef CANVAS_WINDOW_HPP_
#define CANVAS_WINDOW_HPP_

#include "Widget.hpp"

class CanvasWindow: public Widget {
    public:        
        const Color canvasColor_ = Color::WHITE;
        Color color_;

        bool isActive_;
    public:
        CanvasWindow(unsigned x, unsigned y):
            Widget(x, y, 1280, 720),
            color_(Color::BLACK),
            isActive_(false)
            {}
        ~CanvasWindow() {}

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y))
                isActive_ = (isActive_) ? false : true;       
        }

        void draw(sf::RenderWindow& window) override;
};

#endif // CANVAS_WINDOW_HPP_
