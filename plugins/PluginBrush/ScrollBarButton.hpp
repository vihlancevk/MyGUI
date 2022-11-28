#ifndef SCROLL_BAR_BUTTON_HPP_
#define SCROLL_BAR_BUTTON_HPP_

#include "AbstractButton.hpp"

class ScrollBarButton: public AbstractButton {
    public:
        unsigned leftValue_;
        unsigned rightValue_;
        
        unsigned positionX_, positionY_;

        const unsigned pointRadius_ = 10;
    public:
        ScrollBarButton(unsigned x, unsigned y, unsigned weight, unsigned hight, unsigned leftValue, unsigned rightValue):
            AbstractButton(x, y, weight, hight),
            leftValue_(leftValue),
            rightValue_(rightValue),
            positionX_(0),
            positionY_(0)
            {
                positionX_ = x_ + weight_ / 2 - pointRadius_;
                positionY_ = y_ + hight_ / 2 - pointRadius_;
            }
        ~ScrollBarButton() {}

        void contains(Pair<int> point) override {
            if (positionX_ <= (unsigned) point.x && (unsigned) point.x <= positionX_ + 2 * pointRadius_) {
                if (positionY_ <= (unsigned) point.y && (unsigned) point.y <= positionY_ + 2 * pointRadius_) {
                    isContains_ = true;
                    return;
                }
            }

            isContains_ = false;
        }

        void on_mouse_press(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                isActive_ = true;
                isContains_ = false;
            }       
        }

        void on_mouse_release(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                isActive_ = false;
                isContains_ = false;
            }
        }

        void on_mouse_move(Pair<int> point) override {
            if (isActive_ && x_ + pointRadius_ > (unsigned) point.x) {
                isActive_ = false;

                positionX_ = x_ + pointRadius_;
                return;
            }

            if (isActive_ && (unsigned) point.x > x_ + weight_ - pointRadius_) {
                isActive_ = false;

                positionX_ = x_ + weight_ - 3 * pointRadius_;
                return;
            }

            if (isActive_ && (y_ + hight_ / 2 - pointRadius_ > (unsigned) point.y || (unsigned) point.y > y_ + hight_ / 2 + pointRadius_)) {
                isActive_ = false;

                positionX_ = (unsigned) point.x; 
            }

            if (isActive_) {
                if ((unsigned) point.x > x_ + weight_ - 3 * pointRadius_)
                    return;

                positionX_ = (unsigned) point.x;
            }
        }

        void draw(unsigned int* screen, int width, int /*height*/) override {
            unsigned weight = 2;

            // (*) --------------------
            //     |        **        |
            //     |        **        |
            //     --------------------
            for (unsigned j = (y_ + hight_ / 2 - pointRadius_) - weight; j < (y_ + hight_ / 2 - pointRadius_); j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
            
            //     --------------------
            //     |        **        |
            //     |        **        |
            // (*) --------------------
            for (unsigned j = (y_ + hight_ / 2 + pointRadius_); j < (y_ + hight_ / 2 + pointRadius_) + weight; j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
            
            // (*)
            //  --------------------
            //  |        **        |
            //  |        **        |
            //  --------------------
            for (unsigned j = (y_ + hight_ / 2 - pointRadius_); j < (y_ + hight_ / 2 + pointRadius_); j++) {
                for (unsigned i = 4 * (x_); i < 4 * (x_ + weight) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            //                    (*)
            //  --------------------
            //  |        **        |
            //  |        **        |
            //  --------------------
            for (unsigned j = (y_ + hight_ / 2 - pointRadius_); j < (y_ + hight_ / 2 + pointRadius_); j++) {
                for (unsigned i = 4 * (x_ + weight_ - weight); i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            
            //                     
            //  --------------------
            //  |    (*) **        |
            //  |        **        |
            //  --------------------
            for (unsigned j = positionY_; j < positionY_ + 2 * pointRadius_; j++) {
                for (unsigned i = 4 * (positionX_); i < 4 * (positionX_ + 2 * pointRadius_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
        }

        unsigned calculateValue() {
            unsigned length = weight_ - 4 * pointRadius_;
            unsigned value = rightValue_ - leftValue_;
            
            unsigned activeLength = positionX_ - x_ - pointRadius_;
            unsigned activeValue = (value * activeLength) / length + leftValue_;

            return activeValue;
        }
};

#endif // SCROLL_BAR_BUTTON_HPP_
