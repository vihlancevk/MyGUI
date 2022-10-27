#ifndef BUTTON_MANAGER_HPP_
#define BUTTON_MANAGER_HPP_

#include "Button.hpp"

class ButtonManager {
    public:
        size_t size_;
        size_t curSize_;
        Button* buttons_;

        Color curColor_ = Color::BLACK;
     public:
        ButtonManager(size_t size):
            size_(size),
            curSize_(0),
            buttons_((Button*) new char[size_*sizeof(Button)])
            {}
        ~ButtonManager() {
            delete [] (char*)buttons_;
        }

        ButtonManager(const ButtonManager& buttonManager):
            size_(buttonManager.size_),
            curSize_(buttonManager.curSize_),
            buttons_((Button*) new char[size_*sizeof(Button)])
            {
                for (size_t i = 0; i < size_; i ++) {
                    new (&buttons_[i]) Button((buttonManager.buttons_[i]));
                }
            }
        ButtonManager& operator = (const ButtonManager& buttonManager) {
            this->~ButtonManager();
            
            size_ = buttonManager.size_;
            curSize_ = buttonManager.curSize_;
            buttons_ = (Button*) new char[size_*sizeof(Button)];
            for (size_t i = 0; i < size_; i ++) {
                new (&buttons_[i]) Button((buttonManager.buttons_[i]));
            }

            return *this;
        }

        size_t addButton(Button button) {
            if (curSize_ > size_) {
                std::cout << "Array of buttons is full!\n";
                return 0;
            } else {
                buttons_[curSize_++] = button;
                return 1;
            }
        }

        void onMouseClick(unsigned x, unsigned y) {
            bool isActivated = false;
            
            for (size_t i = 0; i < size_; i++) {
                if (!buttons_[i].isActive_)
                    isActivated = true;
                
                buttons_[i].onMouseClick(x, y);

                if (buttons_[i].isActive_ && isActivated) {
                    curColor_ = buttons_[i].color_;

                    for (size_t j = 0; j < size_; j++) {
                        if (j != i)
                            buttons_[j].isActive_ = false;
                    }

                    return;
                } else if (!(buttons_[i].isActive_ || isActivated)) {
                    curColor_ = Color::BLACK;
                } else {
                    isActivated = false;
                }
            }
        }

        void onMouseReleased(unsigned, unsigned) {}

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < size_; i++) {
                buttons_[i].draw(window);
            }
        }
};

#endif // ABSTRACT_BUTTON_MANAGER_HPP_
