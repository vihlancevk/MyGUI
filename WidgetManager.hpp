#ifndef WIDGET_MANAGER_HPP_
#define WIDGET_MANAGER_HPP_

#include "Widget.hpp"

class WidgetManager {
    public:
        size_t size_;
        size_t curSize_;
        Widget** widgets_;
    public:
        WidgetManager(size_t size):
            size_(size),
            curSize_(0),
            widgets_(new Widget*[size_])
            {}

        WidgetManager(const WidgetManager& widgetManager):
            size_(widgetManager.size_),
            curSize_(widgetManager.curSize_),
            widgets_(new Widget*[size_])
            {
                for (size_t i = 0; i < size_; i++) {
                    widgets_[i] = widgetManager.widgets_[i];
                }
            }
        WidgetManager& operator = (const WidgetManager& widgetManager) {
            size_ = widgetManager.size_;
            curSize_ = widgetManager.curSize_;
            delete [] widgets_;
            widgets_ = new Widget*[size_];
            for (size_t i = 0; i < size_; i++) {
                widgets_[i] = widgetManager.widgets_[i];
            }

            return *this;
        }
        ~WidgetManager() {
            delete [] widgets_;
        }

        size_t addWidjet(Widget* widget) {
            if (curSize_ > size_) {
                std::cout << "Array of widjets is full!\n";
                return 0;
            } else {
                widgets_[curSize_++] = widget;
                return 1;
            }
        }

        void onMouseClick(unsigned x, unsigned y) {
            for (size_t i = 0; i < size_; i++) {
                widgets_[i]->onMouseClick(x, y);
            }
        }

        void draw(sf::RenderWindow& window) {
            for (size_t i = 0; i < size_; i++) {
                widgets_[i]->draw(window);
            }
        }
};

#endif // WIDGET_MANAGER_HPP_
