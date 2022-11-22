#ifndef SIZE_BUTTON_HPP_
#define SIZE_BUTTON_HPP_

#include "../AbstractButton.hpp"
#include "../ScrollBarButton.hpp"

class SizeButton: public AbstractButton {
    public:
        unsigned size_ = 10;

        ScrollBarButton scrollBarButton_;
    public:
        SizeButton(unsigned x, unsigned y, unsigned weight, unsigned hight):
            AbstractButton(x, y, weight, hight),
            scrollBarButton_(ScrollBarButton(x, y, weight, hight, 5, 25))
            {}
        ~SizeButton() {}

        void on_mouse_press(Pair<int> point) override {
            scrollBarButton_.on_mouse_press(point);
        }

        void on_mouse_release(Pair<int> point) override {
            scrollBarButton_.on_mouse_release(point);

            size_ = scrollBarButton_.calculateValue();
        }

        void on_mouse_move(Pair<int> point) override {
            scrollBarButton_.on_mouse_move(point);
        }

        void draw(unsigned int* screen, int width, int height) override {
            // (*) --------------------
            //     |                  |
            //     |                  |
            //     |                  |
            //     --------------------
            for (unsigned j = (y_ - outlineThickness_); j < y_; j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
            
            //     --------------------
            //     |                  |
            //     |                  |
            //     |                  |
            // (*) --------------------
            for (unsigned j = (y_ + hight_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 4 * x_; i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }
            
            // (*)
            //  --------------------
            //  |                  |
            //  |                  |
            //  |                  |
            //  --------------------
            for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 4 * (x_ - outlineThickness_); i < 4 * (x_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            //                    (*)
            //  --------------------
            //  |                  |
            //  |                  |
            //  |                  |
            //  --------------------
            for (unsigned j = (y_ - outlineThickness_); j < (y_ + hight_ + outlineThickness_); j++) {
                for (unsigned i = 4 * (x_ + weight_); i < 4 * (x_ + weight_ + outlineThickness_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] = 0;
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            for (unsigned j = y_; j < (y_ + hight_); j++) {
                for (unsigned i = 4 * (x_); i < 4 * (x_ + weight_) - (4 - 1); i += 4) {
                    screen[j * 4 * (unsigned) width + i] =
                    screen[j * 4 * (unsigned) width + i + 1] =
                    screen[j * 4 * (unsigned) width + i + 2] =
                    screen[j * 4 * (unsigned) width + i + 3] = 255;
                }
            }

            scrollBarButton_.draw(screen, width, height);
        }
};

#endif // SIZE_BUTTON_HPP_
