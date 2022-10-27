#ifndef BRUSH_HPP_
#define BRUSH_HPP_

#include "Tool.hpp"

class Brush: public Tool {
    public:
        Brush(unsigned x, unsigned y, const char* image):
            Tool(x, y, image)
            {}
        ~Brush() {}

        void draw(sf::RenderWindow& window) override;
};

#endif // BRUSH_HPP_
