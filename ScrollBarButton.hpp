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
            if (isActive_ && x_ + 2 * pointRadius_ > x) {
                isActive_ = false;

                positionX_ = x_ + 2 * pointRadius_;
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
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f((float) (x_ + 2 * pointRadius_),
                                            (float) (y_ + hight_ / 2));
            line[0].color = sf::Color::Black;
            line[1].position = sf::Vector2f((float) (x_ + weight_ - 2 * pointRadius_),
                                            (float) (y_ + hight_ / 2));
            line[1].color = sf::Color::Black;

            sf::CircleShape point((float) pointRadius_);
            point.setPosition(sf::Vector2f((float) positionX_, (float) positionY_));
            point.setFillColor(sf::Color::Black);

            window.draw(line);
            window.draw(point);
        }

        unsigned calculateValue() {
            unsigned length = weight_ - 4 * pointRadius_, value = rightValue_ - leftValue_;
            unsigned activeLength = positionX_ - x_ - 2 * pointRadius_;
            
            unsigned activeValue = (value * activeLength) / length;

            return activeValue;
        }
};

#endif // SCROLL_BAR_BUTTON_HPP_
