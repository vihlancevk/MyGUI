#ifndef ABSTRACT_BUTTON_HPP_
#define ABSTRACT_BUTTON_HPP_

#include "Widget.hpp"

class AbstractButton: public Widget {
    public:
        unsigned x_;
        unsigned y_;

        unsigned weight_;
        unsigned hight_;
        
        bool isClick_;
        bool isPress_;
    public:
        AbstractButton(unsigned x, unsigned y):
            x_(x),
            y_(y),
            weight_(160),
            hight_(90),
            isClick_(false),
            isPress_(false)
            {}
        ~AbstractButton() {}

        virtual void onClick() {}
        virtual void onPress() {}
};

#endif // BUTTON_HPP_
