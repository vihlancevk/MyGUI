#ifndef SCROLL_BAR_BUTTON_HPP_
#define SCROLL_BAR_BUTTON_HPP_

#include "AbstractButton.hpp"

class ScrollBarButton: public AbstractButton {
    public:
        unsigned leftValue_;
        unsigned rightValue_;
        
        unsigned positionX_, positionY_;

        unsigned pointRadius_ = 10;
    public:
        ScrollBarButton(unsigned x, unsigned y, unsigned leftValue, unsigned rightValue):
            AbstractButton(x, y),
            leftValue_(leftValue),
            rightValue_(rightValue),
            positionX_(0),
            positionY_(0)
            {
                positionX_ = x_ + weight_ / 2 - pointRadius_;
                positionY_ = y_ + hight_ / 2 - pointRadius_;
            }
        ~ScrollBarButton() {}

        bool isPointInWidget(unsigned x, unsigned y) override {
            if (positionX_ - 2 * pointRadius_ <= x && x <= positionX_ + 2 * pointRadius_)
                if (positionY_ - pointRadius_ <= y && y <= positionY_ + pointRadius_)
                    return true;

            return false;
        }

        void onMouseMove(unsigned x, unsigned y) override {
            if (isActive_ && x_ + pointRadius_ > x) {
                isActive_ = false;

                positionX_ = x_ + pointRadius_;
                return;
            }

            if (isActive_ && x > x_ + weight_ - 2 * pointRadius_) {
                isActive_ = false;

                positionX_ = x_ + weight_ - 3 * pointRadius_;
                return;
            }

            if (isActive_ && (y_ + hight_ / 2 - 2 * pointRadius_ > y || y > y_ + hight_ / 2 + pointRadius_)) {
                isActive_ = false;

                positionX_ = x; 
            }

            if (isActive_) {
                positionX_ = x;
            }
        }

        void onMouseClick(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y))
                isActive_ = true;       

        }

        void onMouseReleased(unsigned x, unsigned y) override {
            if (isPointInWidget(x, y)) {
                isActive_ = false;
            }
        }

        void draw(sf::RenderWindow& window) override {
            float weight = 2;

            sf::RectangleShape lineHorizontal(sf::Vector2f((float) weight_, weight));
            lineHorizontal.setFillColor(sf::Color::Black);

            lineHorizontal.setPosition(sf::Vector2f((float) x_, (float) (y_ + hight_ / 2 - pointRadius_) - weight));
            window.draw(lineHorizontal);
            
            lineHorizontal.setPosition(sf::Vector2f((float) x_, (float) (y_ + hight_ / 2 + pointRadius_)));
            window.draw(lineHorizontal);

            sf::RectangleShape lineVerticalLeft(sf::Vector2f((float) (2 * pointRadius_), weight));
            lineVerticalLeft.setPosition(sf::Vector2f((float) x_ + weight, (float) (y_ + hight_ / 2 - pointRadius_)));
            lineVerticalLeft.setFillColor(sf::Color::Black);
            lineVerticalLeft.rotate(90);
            window.draw(lineVerticalLeft);

            sf::RectangleShape lineVerticalRight(sf::Vector2f((float) (2 * pointRadius_), weight));
            lineVerticalRight.setPosition(sf::Vector2f((float) (x_ + weight_), (float) (y_ + hight_ / 2 - pointRadius_)));
            lineVerticalRight.setFillColor(sf::Color::Black);
            lineVerticalRight.rotate(90);
            window.draw(lineVerticalRight);

            sf::CircleShape point((float) pointRadius_);
            point.setPosition(sf::Vector2f((float) positionX_, (float) positionY_));
            point.setFillColor(sf::Color::Black);

            window.draw(point);
        }

        unsigned calculateValue() {
            unsigned length = weight_ - 4 * pointRadius_;
            unsigned value = rightValue_ - leftValue_;
            
            unsigned activeLength = positionX_ - x_ - pointRadius_;
            // std::cout << "length: " << length << ", value: " << value << ", activeLength: " << activeLength << "\n";
            unsigned activeValue = (value * activeLength) / length + leftValue_;

            return activeValue;
        }
};

#endif // SCROLL_BAR_BUTTON_HPP_
