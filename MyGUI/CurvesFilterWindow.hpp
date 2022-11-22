#ifndef CURVES_FILTER_WINDOW_HPP_
#define CURVES_FILTER_WINDOW_HPP_

#include "../Widget.hpp"
#include "Button.hpp"

class CurvesFilterWindow: public Widget {
    public:
        Button okButton_;
        Button cancelButton_;

        bool isActive_ = false;
        unsigned outlineThickness_ = 3;

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

        void draw(unsigned int* screen, int width, int height) override {
            if (isActive_) {
            // (*) --------------------
            //     |                  |
            //     |                  |
            //     |                  |
            //     --------------------
            for (unsigned j = (y_ - outlineThickness_); j < y_; j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
            
            //     --------------------
            //     |                  |
            //     |                  |
            //     |                  |
            // (*) --------------------
            for (unsigned j = (y_ + hight_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
            
            // (*)
            //  --------------------
            //  |                  |
            //  |                  |
            //  |                  |
            //  --------------------
            for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 4 * (x_ - outlineThickness_); i < 4 * (x_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            //                    (*)
            //  --------------------
            //  |                  |
            //  |                  |
            //  |                  |
            //  --------------------
            for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 4 * (x_ + weight_); i < 4 * (x_ + weight_ + outlineThickness_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

                okButton_.draw(screen, width, height);
                cancelButton_.draw(screen, width, height);
            }
        }
};

#endif // CURVES_FILTER_WINDOW_HPP_
