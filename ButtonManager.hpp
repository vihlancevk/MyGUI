#ifndef BUTTON_MANAGER_HPP_
#define BUTTON_MANAGER_HPP_

#include "Widget.hpp"
#include "Button.hpp"

class ButtonManager: Widget {
    public:
        size_t size_;
        Button* elems_;
     public:
        ButtonManager(size_t size, Button buttons, ...):
            size_(size),
            elems_(new Button[size_])
            {
                size_t i = 0;
                for (Button* p = &buttons; i < size_; p++) {
                    elems_[i] = *p;
                    i++;
                }
            }
        
        ButtonManager(const ButtonManager& buttonManager):
            size_(buttonManager.size_),
            elems_(new Button[size_])
            {
                for (size_t i = 0; i < size_; i++) {
                    elems_[i] = buttonManager.elems_[i];
                }
            }
        ButtonManager& operator = (const ButtonManager& buttonManager) {
            size_ = buttonManager.size_;
            delete [] elems_;
            elems_ = new Button[size_];
            for (size_t i = 0; i < size_; i++) {
                elems_[i] = buttonManager.elems_[i];
            }

            return *this;
        }
        ~ButtonManager() {
            delete [] elems_;
        }

        void draw(sf::RenderWindow& window) override {
            for (size_t i = 0; i < size_; i++) {
                elems_[i].draw(window);
            }
        }
};

#endif // ABSTRACT_BUTTON_MANAGER_HPP_
