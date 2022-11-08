#ifndef CURVES_FILTER_WINDOW_HPP_
#define CURVES_FILTER_WINDOW_HPP_

#include "Widget.hpp"

class CurvesFilterWindow: public Widget {
    public:
        bool isActive_ = false;

        float outlineThickness = 3;
    public:
        CurvesFilterWindow(unsigned x, unsigned y, unsigned weight, unsigned hight):
            Widget(x, y, weight, hight)
            {}
        ~CurvesFilterWindow() {}

        virtual void move() override {}

        virtual void onMouseMove(unsigned, unsigned) override {}

        virtual void onMouseClick(unsigned, unsigned) override {}
        
        virtual void onMouseReleased(unsigned, unsigned) override {}
        
        virtual void onKeyboard() override {
            isActive_ = true;
        }

        virtual void draw(sf::RenderWindow& window) override {
            if (isActive_) {
                sf::RectangleShape mainWindow(sf::Vector2f((float) (weight_) + 2 * outlineThickness,
                                                           (float) (hight_) + 2 * outlineThickness));
                mainWindow.setPosition(sf::Vector2f((float) (x_) - outlineThickness,
                                                    (float) (y_) - outlineThickness));
                mainWindow.setFillColor(sf::Color::White);
                mainWindow.setOutlineThickness(outlineThickness);
                mainWindow.setOutlineColor(sf::Color::Black);
                window.draw(mainWindow);
            }
        }

        virtual void close() override {}
};

#endif // CURVES_FILTER_WINDOW_HPP_
