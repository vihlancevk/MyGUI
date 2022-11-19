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

        void draw(unsigned int* /*screen*/, int /*width*/, int /*height*/) override {
            // sf::RectangleShape frame(sf::Vector2f((float) weight_,
            //                                       (float) hight_));
            // frame.setPosition(sf::Vector2f((float) (x_),
            //                                (float) (y_)));
            // frame.setFillColor(sf::Color::White);
            // frame.setOutlineThickness(outlineThickness_);
            // frame.setOutlineColor(sf::Color::Black);

            // window.draw(frame);
            // window.draw(pixels_);

            std::cout << "CanvasWindow::draw(unsigned int*, int, int)\n";
        }
};

#endif // CANVAS_WINDOW_HPP_
