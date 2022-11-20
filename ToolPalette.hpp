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

        void draw(unsigned int* screen, int width, int /*height*/) override {
            if (tool_) {
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

                for (unsigned j = y_; j < (y_ + hight_); j++) {
                    for (unsigned i = 4 * (x_); i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                        screen[j * 4 * (unsigned) width + i] =
                        screen[j * 4 * (unsigned) width + i + 1] =
                        screen[j * 4 * (unsigned) width + i + 2] =
                        screen[j * 4 * (unsigned) width + i + 3] = 255;
                    }
                }

                for (unsigned j = (y_ + hight_ / 2 - tool_->size_ / 2); j < (y_ + hight_ / 2 + tool_->size_ / 2); j++) {
                    for (unsigned i = 4 * (x_ + weight_ / 8); i < 4 * (x_ + 7 * weight_ / 8) - (4 - 1); i += 4) {
                        screen[j * 4 * (unsigned) width + i] = tool_->color_.r;
                        screen[j * 4 * (unsigned) width + i + 1] = tool_->color_.g;
                        screen[j * 4 * (unsigned) width + i + 2] = tool_->color_.b;
                        screen[j * 4 * (unsigned) width + i + 3] = tool_->color_.a;
                    }
                }
            } else {
                for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                    for (unsigned i = 4 * (x_ - outlineThickness_); i < 4 * (x_ + weight_ + outlineThickness_) - (4 - 1); i += 4) {
                        screen[j * 4 * (unsigned) width + i] =
                        screen[j * 4 * (unsigned) width + i + 1] =
                        screen[j * 4 * (unsigned) width + i + 2] =
                        screen[j * 4 * (unsigned) width + i + 3] = 255;
                    }
                }
            }
        }
};

#endif // TOOL_PALETTE_HPP_
