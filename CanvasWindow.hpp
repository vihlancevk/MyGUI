#ifndef CANVAS_WINDOW_HPP_
#define CANVAS_WINDOW_HPP_

#include "Widget.hpp"

class CanvasWindow: public Widget {
    public:
        sf::VertexArray pixels_;

        const Color canvasColor_ = Color::WHITE;
        
        unsigned paintbrushSize_;
        Color paintbrushColor_;

        bool isActive_;
    public:
        CanvasWindow(unsigned x, unsigned y):
            Widget(x, y, 1280, 720),
            pixels_(sf::Points, 1280 * 720),
            paintbrushSize_(5),
            paintbrushColor_(Color::BLACK),
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
            if (isPointInWidget(x, y) && isActive_) {
                unsigned startX = 0;
                if (x - x_ > paintbrushSize_ && (x_ + weight_) - x > paintbrushSize_) {
                    startX = x - x_ - paintbrushSize_;
                } else if ((x_ + weight_) - x <= paintbrushSize_) {
                    startX = weight_ - 2*paintbrushSize_;
                }

                unsigned startY = 0;
                if (y - y_ > paintbrushSize_ && (y_ + hight_) - y > paintbrushSize_) {
                    startY = y - y_ - paintbrushSize_;
                } else if ((y_ + hight_) - y <= paintbrushSize_) {
                    startY = hight_ - 2*paintbrushSize_;
                }

                unsigned startPixel = (startY) * weight_ + (startX);

                for (unsigned i = 0; i < 2*paintbrushSize_; i++) {
                    for (unsigned j = 0; j < 2*paintbrushSize_; j++) {
                        pixels_[startPixel + i * weight_ + j].color = calculateColor(paintbrushColor_);
                    }
                }
            }
        }

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y))
                isActive_ = (isActive_) ? false : true;       
        }

        void draw(sf::RenderWindow& window) override;
};

#endif // CANVAS_WINDOW_HPP_
