#ifndef CANVAS_WINDOW_HPP_
#define CANVAS_WINDOW_HPP_

#include "Widget.hpp"
#include "Tool.hpp"

class CanvasWindow: public Widget {
    public:
        sf::VertexArray pixels_;
        bool isActive_;
        
        const sf::Color canvasColor_ = sf::Color::White;
        Tool* activeTool_ = nullptr;
    public:
        CanvasWindow(unsigned x, unsigned y, unsigned weight, unsigned hight):
            Widget(x, y, weight, hight),
            pixels_(sf::Points, weight * hight),
            isActive_(false)
            {
                for(unsigned i = 0; i < weight_ * hight_; i++) {
                    pixels_[i].position = sf::Vector2f(static_cast<float>(x_ + i % weight_),
                                                       static_cast<float>(y_ + i / weight_));
                    pixels_[i].color = canvasColor_;
                }
            }
        ~CanvasWindow() {}

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
                activeTool_->actionWithCanvas(pixels_, x_, y_, weight_, hight_, (unsigned) point.x, (unsigned) point.y);
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

            for (unsigned j = y_, j1 = 0; j < (y_ + hight_); j++, j1++) {
                for (unsigned i = 4 * (x_), i1 = 0; i < 4 * (x_ + weight_) - (4 - 1); i += 4, i1++) {
                    screen[j * 4 * (unsigned) width + i] = pixels_[j1 * weight_ + i1].color.r;
                    screen[j * 4 * (unsigned) width + i + 1] = pixels_[j1 * weight_ + i1].color.g;
                    screen[j * 4 * (unsigned) width + i + 2] = pixels_[j1 * weight_ + i1].color.b;
                    screen[j * 4 * (unsigned) width + i + 3] = pixels_[j1 * weight_ + i1].color.a;
                }
            }
        }
};

#endif // CANVAS_WINDOW_HPP_
