#ifndef COLOR_BUTTON_MANAGER_HPP_
#define COLOR_BUTTON_MANAGER_HPP_

#include "ColorButton.hpp"

class ColorButtonManager {
    public:
        size_t size_;
        size_t curSize_;
        ColorButton* colorButtons_;

        sf::Color activeColor_ = sf::Color::Black;
     public:
        ColorButtonManager(size_t size):
            size_(size),
            curSize_(0),
            colorButtons_((ColorButton*) new char[size_*sizeof(ColorButton)])
            {}
        ~ColorButtonManager() {
            delete [] (char*) colorButtons_;
        }

        ColorButtonManager(const ColorButtonManager& colorButtonManager):
            size_(colorButtonManager.size_),
            curSize_(colorButtonManager.curSize_),
            colorButtons_((ColorButton*) new char[size_*sizeof(ColorButton)])
            {
                for (size_t i = 0; i < curSize_; i ++) {
                    new (&colorButtons_[i]) ColorButton((colorButtonManager.colorButtons_[i]));
                }
            }
        ColorButtonManager& operator = (const ColorButtonManager& colorButtonManager) {
            this->~ColorButtonManager();
            
            size_ = colorButtonManager.size_;
            curSize_ = colorButtonManager.curSize_;
            colorButtons_ = (ColorButton*) new char[size_*sizeof(ColorButton)];
            for (size_t i = 0; i < curSize_; i ++) {
                new (&colorButtons_[i]) ColorButton((colorButtonManager.colorButtons_[i]));
            }

            return *this;
        }

        size_t addColorButton(ColorButton colorButton) {
            if (curSize_ >= size_) {
                std::cout << "Array of buttons is full!\n";
                return 0;
            } else {
                :: new (&colorButtons_[curSize_ ++]) ColorButton(colorButton);
                return 1;
            }
        }

        void onMouseMove(unsigned x, unsigned y) {
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].onMouseMove(x, y);
            }
        }

        void onMouseClick(unsigned x, unsigned y) {
            for (size_t i = 0; i < 3; i++) {
                colorButtons_[i].onMouseClick(x, y);
            }
        }

        void onMouseReleased(unsigned x, unsigned y) {
            unsigned color[3] = {};

            for (size_t i = 0; i < 3; i++) {
                colorButtons_[i].onMouseReleased(x, y);
                color[i] = colorButtons_[i].scrollBarButton_.calculateValue();
            }
            
            activeColor_ = sf::Color((sf::Uint8) color[0],
                                     (sf::Uint8) color[1],
                                     (sf::Uint8) color[2]);
        }

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < size_; i++) {
                colorButtons_[i].draw(window);
            }
        }
};

#endif // COLOR_BUTTON_MANAGER_HPP_
