#ifndef COLOR_BUTTON_MANAGER_HPP_
#define COLOR_BUTTON_MANAGER_HPP_

#include "ColorButton.hpp"

class ColorButtonManager {
    public:
        static const size_t size_ = 3;
        size_t curSize_ = 0;
        ColorButton* colorButtons_;

        sf::Color activeColor_ = sf::Color::Black;
     public:
        ColorButtonManager():
            colorButtons_((ColorButton*) new char[size_*sizeof(ColorButton)])
            {}
        ~ColorButtonManager() {
            delete [] (char*) colorButtons_;
        }

        ColorButtonManager(const ColorButtonManager& colorButtonManager):
            curSize_(colorButtonManager.curSize_),
            colorButtons_((ColorButton*) new char[size_*sizeof(ColorButton)])
            {
                for (size_t i = 0; i < curSize_; i ++) {
                    new (&colorButtons_[i]) ColorButton((colorButtonManager.colorButtons_[i]));
                }
            }
        ColorButtonManager& operator = (const ColorButtonManager& colorButtonManager) {
            this->~ColorButtonManager();
            
            curSize_ = colorButtonManager.curSize_;
            colorButtons_ = (ColorButton*) new char[size_*sizeof(ColorButton)];
            for (size_t i = 0; i < curSize_; i ++) {
                new (&colorButtons_[i]) ColorButton((colorButtonManager.colorButtons_[i]));
            }

            return *this;
        }

        size_t addColorButton(ColorButton colorButton) {
            if (curSize_ >= size_) {
                std::cout << "Array of color buttons is full!\n";
                return 0;
            } else {
                :: new (&colorButtons_[curSize_++]) ColorButton(colorButton);
                return 1;
            }
        }

        void onMouseMove(unsigned x, unsigned y) {
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].onMouseMove(x, y);
            }
        }

        void onMouseClick(unsigned x, unsigned y) {
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].onMouseClick(x, y);
            }
        }

        void onMouseReleased(unsigned x, unsigned y) {
            unsigned color[size_] = {};

            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].onMouseReleased(x, y);
                color[i] = colorButtons_[i].scrollBarButton_.calculateValue();
            }
            
            activeColor_ = sf::Color((sf::Uint8) color[0],
                                     (sf::Uint8) color[1],
                                     (sf::Uint8) color[2]);
        }

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].draw(window);
            }
        }
};

#endif // COLOR_BUTTON_MANAGER_HPP_
