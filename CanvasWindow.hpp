#ifndef CANVAS_WINDOW_HPP_
#define CANVAS_WINDOW_HPP_

#include "Widget.hpp"
#include "Tool.hpp"

class CanvasWindow: public Widget {
    public:
        sf::VertexArray pixels_;
        bool isActive_;
        
        const Color canvasColor_ = Color::WHITE;
        Tool* activeTool_ = nullptr;
    public:
        CanvasWindow(unsigned x, unsigned y):
            Widget(x, y, 1280, 720),
            pixels_(sf::Points, 1280 * 720),
            isActive_(false)
            {
                for(unsigned i = 0; i < weight_ * hight_; i++) {
                    pixels_[i].position = sf::Vector2f(static_cast<float>(x_ + i % weight_),
                                                       static_cast<float>(y_ + i / weight_));
                    pixels_[i].color = calculateColor(canvasColor_);
                }
            }
        ~CanvasWindow() {}

        void onMouseMove(unsigned x, unsigned y) override {
            if (!isPointInWidget(x, y)) {
                isActive_ = false;
            }

            if (isActive_ && activeTool_) {
                activeTool_->actionWithCanvas(pixels_, x_, y_, weight_, hight_, x, y);
            }
        }

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y))
                isActive_ = true;       
        }

        void onMouseReleased(unsigned x, unsigned y) override {
            if(isPointInWidget(x, y))
                isActive_ = false;
        }

        void draw(sf::RenderWindow& window) override;
};

#endif // CANVAS_WINDOW_HPP_
