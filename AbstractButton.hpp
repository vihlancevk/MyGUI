#ifndef ABSTRACT_BUTTON_HPP_
#define ABSTRACT_BUTTON_HPP_

#include "Widget.hpp"

class AbstractButton: public Widget {
    public:
        bool isActive_;
    public:
        AbstractButton(unsigned x, unsigned y, unsigned weight, unsigned hight):
            Widget(x, y, weight, hight),
            isActive_(false)
            {}

        ~AbstractButton() {}

        void on_mouse_press(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                isActive_ = (isActive_) ? false : true;
                isContains_ = false;
            }
        }
};

#endif // BUTTON_HPP_
