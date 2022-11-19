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
            if (positionX_ <= (unsigned) point.x && (unsigned) point.x <= positionX_ + 2 * pointRadius_)
                if (positionY_ <= (unsigned) point.y && (unsigned) point.y <= positionY_ + 2 * pointRadius_)
                    isContains_ = true;

            isContains_ = false;
        }

        void on_mouse_press(Pair<int> point) override {
            contains(point);
            if (isContains_)
                isActive_ = true;       
        }

        void on_mouse_release(Pair<int> point) override {
            contains(point);
            if (isContains_) {
                isActive_ = false;
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

            for (unsigned j = (y_ + hight_ / 2 - pointRadius_) - weight; j < (y_ + hight_ / 2 - pointRadius_); j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            // sf::RectangleShape lineHorizontal(sf::Vector2f((float) weight_, weight));
            // lineHorizontal.setFillColor(sf::Color::Black);

            // lineHorizontal.setPosition(sf::Vector2f((float) x_, (float) (y_ + hight_ / 2 - pointRadius_) - weight));
            // window.draw(lineHorizontal);
            
            // lineHorizontal.setPosition(sf::Vector2f((float) x_, (float) (y_ + hight_ / 2 + pointRadius_)));
            // window.draw(lineHorizontal);

            // sf::RectangleShape lineVerticalLeft(sf::Vector2f((float) (2 * pointRadius_), weight));
            // lineVerticalLeft.setPosition(sf::Vector2f((float) x_ + weight, (float) (y_ + hight_ / 2 - pointRadius_)));
            // lineVerticalLeft.setFillColor(sf::Color::Black);
            // lineVerticalLeft.rotate(90);
            // window.draw(lineVerticalLeft);

            // sf::RectangleShape lineVerticalRight(sf::Vector2f((float) (2 * pointRadius_), weight));
            // lineVerticalRight.setPosition(sf::Vector2f((float) (x_ + weight_), (float) (y_ + hight_ / 2 - pointRadius_)));
            // lineVerticalRight.setFillColor(sf::Color::Black);
            // lineVerticalRight.rotate(90);
            // window.draw(lineVerticalRight);

            // sf::CircleShape point((float) pointRadius_);
            // point.setPosition(sf::Vector2f((float) positionX_, (float) positionY_));
            // point.setFillColor(sf::Color::Black);

            // window.draw(point);
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
