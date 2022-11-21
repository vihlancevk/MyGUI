#ifndef CANVAS_WINDOW_HPP_
#define CANVAS_WINDOW_HPP_

#include "Widget.hpp"
#include "plugin.h"

class CanvasWindow: public Widget {
    public:
        unsigned* pixels_;
        bool isActive_;
        
        const sf::Color canvasColor_ = sf::Color::White;
        ITool* activeTool_ = nullptr;
    public:
        CanvasWindow(unsigned x, unsigned y, unsigned weight, unsigned hight):
            Widget(x, y, weight, hight),
            pixels_(new unsigned[4 * weight * hight]),
            isActive_(false)
            {
                for(unsigned i = 0; i < 4 * weight_ * hight_; i += 4) {
                    pixels_[i] = canvasColor_.r;
                    pixels_[i + 1] = canvasColor_.g;
                    pixels_[i + 2] = canvasColor_.b;
                    pixels_[i + 3] = canvasColor_.a;
                }
            }
        ~CanvasWindow() {
            delete [] pixels_;
        }

        CanvasWindow(const CanvasWindow& canvasWindow) = delete;
        CanvasWindow& operator = (const CanvasWindow& canvasWindow) = delete;

        void on_mouse_press(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                isActive_ = true;
                isContains_ = false;
            }       
        }

        void on_mouse_release(Pair<int> point) override {
            contains(point);
            if(isContains_) {
                isActive_ = false;
                isContains_ = false;
            }
        }

        void on_mouse_move(Pair<int> point) override {
            contains(point);
            if (!isContains_) {
                isActive_ = false;
            }

            if (isActive_ && activeTool_) {
                activeTool_->apply(pixels_, (int) weight_, (int) hight_, Pair<int>{point.x - (int) x_, point.y - (int) y_});
            }
        }

        void draw(unsigned int* screen, int width, int /*height*/) override {
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

            for (unsigned j = y_, j1 = 0; j1 < hight_; j++, j1++) {
                for (unsigned i = 4 * (x_), i1 = 0; i1 < 4 * weight_ - (4 - 1); i += 4, i1 += 4) {
                    screen[j * 4 * (unsigned) width + i] = pixels_[j1 * 4 * weight_ + i1];
                    screen[j * 4 * (unsigned) width + i + 1] = pixels_[j1 * 4 * weight_ + i1 + 1];
                    screen[j * 4 * (unsigned) width + i + 2] = pixels_[j1 * 4 * weight_ + i1 + 2];
                    screen[j * 4 * (unsigned) width + i + 3] = pixels_[j1 * 4 * weight_ + i1 + 3];
                }
            }
        }
};

#endif // CANVAS_WINDOW_HPP_
