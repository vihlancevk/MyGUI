#ifndef TOOL_BUTTON_HPP_
#define TOOL_BUTTON_HPP_

#include "AbstractButton.hpp"
#include "Tool.hpp"

class ToolButton: public AbstractButton {
    public:
        sf::Image image_;

        size_t size_ = 1;
        size_t curSize_ = 0;
        Tool** tool_;
    public:
        ToolButton(unsigned x, unsigned y, unsigned weight, unsigned hight, const char* image):
            AbstractButton(x, y, weight, hight),
            image_(),
            tool_((Tool**) new char[sizeof(Tool*)])
            {
                image_.loadFromFile(image);
            }
        ~ToolButton() {
            delete [] (char*) tool_;
        }

        ToolButton(const ToolButton& toolButton) = delete;
        ToolButton& operator = (const ToolButton& toolButton) = delete;

        size_t setTool(Tool* tool) {
            if (curSize_ >= size_) {
                std::cout << "Tool in ToolButton already set!\n";
                return 0;
            } else {
                tool_[curSize_++] = tool;
                return 1;
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

            for (unsigned j = y_; j < (y_ + hight_); j++) {
                for (unsigned i = 4 * (x_); i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] =
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            // sf::Texture texture;
            // texture.loadFromImage(image_, sf::IntRect(0, 0, (int) weight_, (int) hight_));

            // sf::Sprite sprite;
            // sprite.setTexture(texture);
            // sprite.setPosition((float) x_, (float) y_);
            
            // window.draw(sprite);

            if (isActive_) {
                const unsigned pointRadius = 5;
                
                //                     
                //  --------------------
                //  |(*)*              |
                //  |                  |
                //  |                  |
                //  --------------------
                for (unsigned j = y_ + pointRadius; j < (y_ + 2 * pointRadius); j++) {
                    for (unsigned i = 4 * (x_ + pointRadius); i < 4 * (x_ + 2 * pointRadius) - (4 - 1); i += 4) {
                        screen[j * 4 * (unsigned) width + i] =
                        screen[j * 4 * (unsigned) width + i + 1] =
                        screen[j * 4 * (unsigned) width + i + 2] = 0;
                        screen[j * 4 * (unsigned) width + i + 3] = 255;
                    }
                }
            }
        }
};

#endif // TOOL_BUTTON_HPP_
