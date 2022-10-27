#ifndef TOOL_HPP_
#define TOOL_HPP_

#include "AbstractButton.hpp"

class Tool: public AbstractButton {
    public:
        sf::Image image_;
    public:
        Tool(unsigned x, unsigned y, const char* image):
            AbstractButton(x, y),
            image_()
            {
                image_.loadFromFile(image);
            }
        ~Tool() {}
};

#endif // TOOL_HPP_
