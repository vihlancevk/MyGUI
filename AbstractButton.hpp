#ifndef ABSTRACT_BUTTON_HPP_
#define ABSTRACT_BUTTON_HPP_

#include "Widget.hpp"

class AbstractButton: public Widget {
    public:
        bool isActive_;
    public:
        AbstractButton(unsigned x, unsigned y):
            Widget(x, y, 160, 90),
            isActive_(false)
            {}
        ~AbstractButton() {}
};

#endif // BUTTON_HPP_
