#ifndef BUTTON_MANAGER_HPP_
#define BUTTON_MANAGER_HPP_

#include "Widget.hpp"
#include "Button.hpp"

class ButtonManager: public Widget {
    public:
        size_t size_;
        size_t curSize_;
        AbstractButton** buttons_;
     public:
        ButtonManager(size_t size):
            Widget(),
            size_(size),
            curSize_(0),
            buttons_(new AbstractButton*[size_])
            {}
        
        ButtonManager(const ButtonManager& buttonManager):
            Widget(),
            size_(buttonManager.size_),
            curSize_(buttonManager.curSize_),
            buttons_(new AbstractButton*[size_])
            {
                for (size_t i = 0; i < size_; i++) {
                    buttons_[i] = buttonManager.buttons_[i];
                }
            }
        ButtonManager& operator = (const ButtonManager& buttonManager) {
            size_ = buttonManager.size_;
            curSize_ = buttonManager.curSize_;
            delete [] buttons_;
            buttons_ = new AbstractButton*[size_];
            for (size_t i = 0; i < size_; i++) {
                buttons_[i] = buttonManager.buttons_[i];
            }

            return *this;
        }
        ~ButtonManager() {
            delete [] buttons_;
        }

        size_t addButton(AbstractButton* abstractButton) {
            if (curSize_ > size_) {
                std::cout << "Array of buttons is full!\n";
                return 0;
            } else {
                buttons_[curSize_++] = abstractButton;
                return 1;
            }
        }

        void onMouseClick(unsigned x, unsigned y) override {
            bool isActivated = false;
            
            for (size_t i = 0; i < size_; i++) {
                if (!buttons_[i]->isActive_)
                    isActivated = true;
                
                buttons_[i]->onMouseClick(x, y);

                if (buttons_[i]->isActive_ && isActivated) {
                    for (size_t j = 0; j < size_; j++) {
                        if (j != i)
                            buttons_[j]->isActive_ = false;
                    }

                    break;
                } else {
                    isActivated = false;
                }
            }
        }

        void draw(sf::RenderWindow& window) override {
            for (size_t i = 0; i < size_; i++) {
                buttons_[i]->draw(window);
            }
        }
};

#endif // ABSTRACT_BUTTON_MANAGER_HPP_
