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

        void onMouseMove(unsigned x, unsigned y) {
            sizeButtons_.onMouseMove(x, y);
        }

        void onMouseClick(unsigned x, unsigned y) {
            sizeButtons_.onMouseClick(x, y);
        }

        void onMouseReleased(unsigned x, unsigned y) {
            sizeButtons_.onMouseReleased(x, y);

            activeSize_ = sizeButtons_.size_;
        }

        void draw(sf::RenderWindow& window) {
                sizeButtons_.draw(window);
        }
};

#endif // SIZE_BUTTON_MANAGER_HPP_
