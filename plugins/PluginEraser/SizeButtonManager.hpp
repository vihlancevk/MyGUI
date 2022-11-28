#ifndef SIZE_BUTTON_MANAGER_HPP_
#define SIZE_BUTTON_MANAGER_HPP_

#include "SizeButton.hpp"

class SizeButtonManager {
    public:
        SizeButton sizeButtons_;

        unsigned activeSize_ = 10;
     public:
        SizeButtonManager(SizeButton& sizeButton):
            sizeButtons_(sizeButton)
            {}
        ~SizeButtonManager() {}

        void on_mouse_press(Pair<int> point) {
            sizeButtons_.on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) {
            sizeButtons_.on_mouse_release(point);

            activeSize_ = sizeButtons_.size_;
        }

        void on_mouse_move(Pair<int> point) {
            sizeButtons_.on_mouse_move(point);
        }

        void draw(unsigned int* screen, int width, int height) {
                sizeButtons_.draw(screen, width, height);
        }
};

#endif // SIZE_BUTTON_MANAGER_HPP_
