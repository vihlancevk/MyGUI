#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "plugin.h"

class Widget: public IWidget {
    public:
        unsigned x_, y_;

        unsigned weight_, hight_;

        bool isContains_ = false;

        unsigned outlineThickness_ = 3;
    public:
        Widget(unsigned x, unsigned y, unsigned weight, unsigned hight):
            IWidget(),
            x_(x),
            y_(y),
            weight_(weight),
            hight_(hight)
            {}
        ~Widget() {};

        void set_pos(Pair<int> /*point*/) override {
            std::cout << "Widget::set_pos(Pair<int>)\n";
        }
        
        Pair<int> get_pos() override {
            std::cout << "Widget::get_pos()\n";

            return Pair<int>{(int) x_, (int) y_};
        }

        Pair<int> get_size() override {
            std::cout << "Widget::get_size()\n";

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

        void on_mouse_press(Pair<int> /*point*/) override {
            std::cout << "Widget::on_mouse_press(Pair<int>)\n";
        }

        void on_mouse_release(Pair<int> /*point*/) override {
            std::cout << "Widget::on_mouse_release(Pair<int>)\n";
        }

        void on_mouse_move(Pair<int> /*point*/) override {
            std::cout << "Widget::on_mouse_move(Pair<int>)\n";
        }
        
        void on_key_press(int /*key*/) override {
            std::cout << "Widget::on_key_press(int)\n";
        }

        void on_key_release(int /*key*/) override {
            std::cout << "Widget::on_key_release(int)\n";
        }

        void draw(unsigned int* /*screen*/, int /*width*/, int /*height*/) override {
            std::cout << "Widget::draw(unsigned int*, int, int)\n";
        }
};

#endif // WIDGET_HPP_
