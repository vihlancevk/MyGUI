#ifndef PROPS_HPP_
#define PROPS_HPP_

#include <iostream>
#include "plugin.h"
#include "ColorButtonManager.hpp"
#include "SizeButtonManager.hpp"
#include "ToolPalette.hpp"

class Props: public IWidget {
    public:
        ColorButtonManager* colorButtonManager_;
        SizeButtonManager* sizeButtonManager_;
        ToolPalette toolPalette_;

        sf::Color activeColor_ = sf::Color::Black;
        unsigned size_ = 10;
    public:
        Props(ColorButtonManager* colorButtonManager,
              SizeButtonManager* SizeButtonManager,
              ToolPalette& toolPalette):
                colorButtonManager_(colorButtonManager),
                sizeButtonManager_(SizeButtonManager),
                toolPalette_(toolPalette)
                {}

        ~Props() {}

        Props(const Props& props) = delete;
        Props& operator = (const Props& props) = delete;        

        void set_pos(Pair<int> /*point*/) override {
            std::cout << "Props::set_pos(Pair<int> point)\n";
        }

        Pair<int> get_pos() override {
            std::cout << "Props::get_pos()\n";

            return Pair<int>{0, 0};
        }

        Pair<int> get_size() override {
            std::cout << "Props::get_size()\n";

            return Pair<int>{0, 0};
        }

        void contains(Pair<int> /*point*/) override {
            std::cout << "Props::contains(Pair<int> point)\n";
        }

        void on_mouse_press(Pair<int> point) override {
            colorButtonManager_->on_mouse_press(point);

            sizeButtonManager_->on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) override {
            colorButtonManager_->on_mouse_release(point);

            sizeButtonManager_->on_mouse_release(point);

            toolPalette_.color_ = colorButtonManager_->activeColor_;
            toolPalette_.size_ = sizeButtonManager_->activeSize_;
        }

        void on_mouse_move(Pair<int> point) override {
            colorButtonManager_->on_mouse_move(point);
            
            sizeButtonManager_->on_mouse_move(point);
        }

        void on_key_press(int /*key*/) override {
            std::cout << "Props::on_key_press(int key)\n";
        }

        void on_key_release(int /*key*/) override {
            std::cout << "Props::on_key_release(int key)\n";
        }

        void draw(unsigned int* screen, int width, int height) override {
            colorButtonManager_->draw(screen, width, height);

            sizeButtonManager_->draw(screen, width, height);
            
            toolPalette_.draw(screen, width, height);
        }
};

#endif // PROPS_HPP_
