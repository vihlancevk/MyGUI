#ifndef TOOL_BUTTON_HPP_
#define TOOL_BUTTON_HPP_

#include <iostream>
#include "plugin.h"
#include "PluginEraser.hpp"
#include "Eraser.hpp"
#include "PropsEraser.hpp"

class ToolButton: public IPushButton {
    public:
        unsigned x_, y_;
        unsigned weight_, hight_;

        sf::Image image_;

        PluginEraser* plugin_;

        bool isContains_ = false;

        unsigned outlineThickness_ = 3;
    public:
        ToolButton(unsigned x, unsigned y, unsigned weight, unsigned hight, const char* image):
            IPushButton(),
            x_(x),
            y_(y),
            weight_(weight),
            hight_(hight),
            image_(),
            plugin_(nullptr)
            {
                set_state(false);
                image_.loadFromFile(image);
            }

        ~ToolButton() {}

        // TODO: write a copy constructor and assignment operator
        ToolButton(const ToolButton& toolButton) = delete;
        ToolButton& operator = (const ToolButton& toolButton) = delete;

        void set_plugin(PluginEraser* plugin) {
            plugin_ = plugin;
        }

        void set_signal(void (* /*signal*/)(IPushButton*)) override {
            ((Eraser*) plugin_->get_tool())->size_ = ((Props*) plugin_->get_props())->toolPalette_.size_;
            ((Eraser*) plugin_->get_tool())->color_ = ((Props*) plugin_->get_props())->toolPalette_.color_;
            ((Props*) plugin_->get_props())->toolPalette_.isActive_ = (((ToolButton*) plugin_->get_tool_button())->get_state()) ? true : false;
            ((Props*) plugin_->get_props())->isActive_ = (((ToolButton*) plugin_->get_tool_button())->get_state()) ? true : false;
        }

        void set_pos(Pair<int> /*point*/) override {
            std::cout << "ToolButton::set_pos(Pair<int>)\n";
        }
        
        Pair<int> get_pos() override {
            std::cout << "ToolButton::get_pos()\n";

            return Pair<int>{(int) x_, (int) y_};
        }

        Pair<int> get_size() override {
            std::cout << "ToolButton::get_size()\n";

            return Pair<int>{(int) weight_, (int) hight_};
        }

        void contains(Pair<int> point) override {         
            if (x_ <= (unsigned) point.x && (unsigned) point.x <= (x_ + weight_)) {
                if (y_ <= (unsigned) point.y && (unsigned) point.y <= (y_ + hight_)) {
                    isContains_ = true;
                    return;
                }
            }

            isContains_ = false;
        }        

        void on_mouse_press(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                if (this->get_state()) {
                    this->set_state(false);
                } else {
                    this->set_state(true);
                }
                isContains_ = false;
            }
        }

        void on_mouse_release(Pair<int> /*point*/) override {
            std::cout << "ToolButton::on_mouse_release(Pair<int>)\n";
        }

        void on_mouse_move(Pair<int> /*point*/) override {
            std::cout << "ToolButton::on_mouse_move(Pair<int>)\n";
        }
        
        void on_key_press(int /*key*/) override {
            std::cout << "ToolButton::on_key_press(int)\n";
        }

        void on_key_release(int /*key*/) override {
            std::cout << "ToolButton::on_key_release(int)\n";
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

            const unsigned char* pixels = image_.getPixelsPtr();
            for (unsigned j = y_; j < (y_ + hight_); j++) {
                for (unsigned i = 4 * (x_); i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] = pixels[(j - y_) * 4 * (unsigned) weight_ + (i - 4 * (x_))];
                    screen[j * 4 * (unsigned) width + i + 1] = pixels[(j - y_) * 4 * (unsigned) weight_ + (i - 4 * (x_)) + 1];
                    screen[j * 4 * (unsigned) width + i + 2] = pixels[(j - y_) * 4 * (unsigned) weight_ + (i - 4 * (x_)) + 2];
                    screen[j * 4 * (unsigned) width + i + 3] = pixels[(j - y_) * 4 * (unsigned) weight_ + (i - 4 * (x_)) + 3];
                }
            }

            if (this->get_state()) {
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
