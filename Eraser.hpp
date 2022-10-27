#ifndef ERASER_HPP_
#define ERASER_HPP_

#include "Tool.hpp"

class Eraser: public Tool {
    public:
        Eraser(unsigned x, unsigned y, const char* image):
            Tool(x, y, image)
            {}
        ~Eraser() {}

        void draw(sf::RenderWindow& window) override;
};

#endif // ERASER_HPP_
