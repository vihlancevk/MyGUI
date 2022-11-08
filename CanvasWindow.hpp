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

        void draw(sf::RenderWindow& window) override {
            sf::RectangleShape frame(sf::Vector2f((float) weight_ + 2 * outlineThickness_,
                                                  (float) hight_ + 2 * outlineThickness_));
            frame.setPosition(sf::Vector2f((float) (x_) - outlineThickness_,
                                           (float) (y_) - outlineThickness_));
            frame.setFillColor(sf::Color::White);
            frame.setOutlineThickness(outlineThickness_);
            frame.setOutlineColor(sf::Color::Black);

            window.draw(frame);
            window.draw(pixels_);
        }
};

#endif // CANVAS_WINDOW_HPP_
