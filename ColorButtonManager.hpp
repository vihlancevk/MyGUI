#ifndef COLOR_BUTTON_MANAGER_HPP_
#define COLOR_BUTTON_MANAGER_HPP_

#include "ColorButton.hpp"

class ColorButtonManager {
    public:
        size_t size_;
        size_t curSize_;
        ColorButton* colorButtons_;

        Color activeColor_ = Color::BLACK;
     public:
        ColorButtonManager(size_t size):
            size_(size),
            curSize_(0),
            colorButtons_((ColorButton*) new char[size_*sizeof(ColorButton)])
            {}
        ~ColorButtonManager() {
            delete [] (char*)colorButtons_;
        }

        ColorButtonManager(const ColorButtonManager& colorButtonManager):
            size_(colorButtonManager.size_),
            curSize_(colorButtonManager.curSize_),
            colorButtons_((ColorButton*) new char[size_*sizeof(ColorButton)])
            {
                for (size_t i = 0; i < size_; i ++) {
                    new (&colorButtons_[i]) ColorButton((colorButtonManager.colorButtons_[i]));
                }
            }
        ColorButtonManager& operator = (const ColorButtonManager& colorButtonManager) {
            this->~ColorButtonManager();
            
            size_ = colorButtonManager.size_;
            curSize_ = colorButtonManager.curSize_;
            colorButtons_ = (ColorButton*) new char[size_*sizeof(ColorButton)];
            for (size_t i = 0; i < size_; i ++) {
                new (&colorButtons_[i]) ColorButton((colorButtonManager.colorButtons_[i]));
            }

            return *this;
        }

        size_t addButton(ColorButton colorButton) {
            if (curSize_ > size_) {
                std::cout << "Array of buttons is full!\n";
                return 0;
            } else {
                colorButtons_[curSize_++] = colorButton;
                return 1;
            }
        }

        void onMouseClick(unsigned x, unsigned y) {
            bool isActivated = false;
            
            for (size_t i = 0; i < size_; i++) {
                if (!colorButtons_[i].isActive_)
                    isActivated = true;
                
                colorButtons_[i].onMouseClick(x, y);

                if (colorButtons_[i].isActive_ && isActivated) {
                    activeColor_ = colorButtons_[i].color_;

                    for (size_t j = 0; j < size_; j++) {
                        if (j != i)
                            colorButtons_[j].isActive_ = false;
                    }

                    return;
                } else if (!(colorButtons_[i].isActive_ || isActivated)) {
                    activeColor_ = Color::BLACK;
                } else {
                    isActivated = false;
                }
            }
        }

        void onMouseReleased(unsigned, unsigned) {}

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < size_; i++) {
                colorButtons_[i].draw(window);
            }
        }
};

#endif // COLOR_BUTTON_MANAGER_HPP_
