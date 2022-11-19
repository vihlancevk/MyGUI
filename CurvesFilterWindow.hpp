#ifndef CURVES_FILTER_WINDOW_HPP_
#define CURVES_FILTER_WINDOW_HPP_

#include "Widget.hpp"
#include "Button.hpp"

class CurvesFilterWindow: public Widget {
    public:
        Button okButton_;
        Button cancelButton_;

        bool isActive_ = false;
        float outlineThickness_ = 3;

        int prevCode_ = 0;
    public:
        CurvesFilterWindow(unsigned x, unsigned y, unsigned weight, unsigned hight):
            Widget(x, y, weight, hight),
            okButton_(x + 17 * weight / 20, y + hight / 20, weight / 10, 2 * hight / 20, "OK"),
            cancelButton_(x + 17 * weight / 20, y + 4 * hight / 20, weight / 10, 2 * hight / 20, "CANCEL")
            {}
        ~CurvesFilterWindow() {}

        void on_mouse_press(Pair<int> point) override {
            okButton_.on_mouse_press(point);
            cancelButton_.on_mouse_press(point);

            if (okButton_.isActive_) {
                isActive_ = false;
                std::cout << "Change save!\n";
                return;
            }
            if (cancelButton_.isActive_) {
                isActive_ = false;
                std::cout << "Change don`t save!\n";
            }
        }
        
        void on_mouse_release(Pair<int> /*point*/) override {
            std::cout << "CurvesFilterWindow::on_mouse_release(Pair<int>)\n";
        }
        
        void on_mouse_move(Pair<int> /*point*/) override {
            std::cout << "CurvesFilterWindow::on_mouse_move(Pair<int>)\n";
        }

        void on_key_press(int key) override {
            if (prevCode_ == sf::Keyboard::LControl) {
                if (key == sf::Keyboard::N) {
                    isActive_ = true;
                }
            }

            prevCode_ = key;
        }

        void draw(unsigned int* /*screen*/, int /*width*/, int /*height*/) override {
            // if (isActive_) {
            //     sf::RectangleShape mainWindow(sf::Vector2f((float) (weight_),
            //                                                (float) (hight_)));
            //     mainWindow.setPosition(sf::Vector2f((float) (x_),
            //                                         (float) (y_)));
            //     mainWindow.setFillColor(sf::Color::White);
            //     mainWindow.setOutlineThickness(outlineThickness_);
            //     mainWindow.setOutlineColor(sf::Color::Black);
            //     window.draw(mainWindow);

            //     okButton_.draw(window);
            //     cancelButton_.draw(window);
            // }

            std::cout << "CurvesFilterWindow::draw(unsigned int*, int, int)\n";
        }
};

#endif // CURVES_FILTER_WINDOW_HPP_
