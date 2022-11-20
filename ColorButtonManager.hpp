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

        void on_mouse_press(Pair<int> point) {
            std::cout << "OK\n";
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].on_mouse_press(point);
            }
        }

        void on_mouse_release(Pair<int> point) {
            unsigned color[size_] = {};

            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].on_mouse_release(point);
                color[i] = colorButtons_[i].scrollBarButton_.calculateValue();
            }
            
            activeColor_ = sf::Color((sf::Uint8) color[0],
                                     (sf::Uint8) color[1],
                                     (sf::Uint8) color[2]);
        }

        void on_mouse_move(Pair<int> point) {
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].on_mouse_move(point);
            }
        }

        void draw(unsigned int* screen, int width, int height) {
            for (size_t i = 0; i < curSize_; i++) {
                colorButtons_[i].draw(screen, width, height);
            }
        }
};

#endif // COLOR_BUTTON_MANAGER_HPP_
