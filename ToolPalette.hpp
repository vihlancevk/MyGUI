#ifndef TOOL_PALETTE_HPP_
#define TOOL_PALETTE_HPP_

#include "Widget.hpp"

class ToolPalette: public Widget {
    public:
        Tool* tool_ = nullptr;
    public:
        ToolPalette(unsigned x, unsigned y, unsigned weight, unsigned hight):
            Widget(x , y, weight, hight)
            {}
        ~ToolPalette() {}

        ToolPalette(const ToolPalette& toolPalette) = delete;
        ToolPalette& operator = (const ToolPalette& toolPalette) = delete;

        void setTool(Tool* tool) {
            tool_ = tool;
        }

        void draw(unsigned int* /*screen*/, int /*width*/, int /*height*/) override {
            // sf::RectangleShape toolPalette(sf::Vector2f((float) weight_,
            //                                             (float) hight_));
            // toolPalette.setPosition(sf::Vector2f((float) x_, (float) y_));
            // toolPalette.setFillColor(sf::Color::White);
            // toolPalette.setOutlineThickness(outlineThickness_);
            // toolPalette.setOutlineColor(sf::Color::Black);

            // if (tool_) {
            //     sf::RectangleShape line(sf::Vector2f((float) (3 * weight_ / 4), (float) tool_->size_));
            //     line.setPosition(sf::Vector2f((float) (x_ + (weight_ / 8)), (float) (y_ + hight_ / 2 - tool_->size_ / 2)));
            //     line.setFillColor(tool_->color_);

            //     window.draw(toolPalette);
            //     window.draw(line);
            // }

            std::cout << "ToolPalatte::draw(unsigned int*, int, int)\n";
        }
};

#endif // TOOL_PALETTE_HPP_
