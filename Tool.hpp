#ifndef TOOL_HPP_
#define TOOL_HPP_

#include "AbstractButton.hpp"

class Tool: public AbstractButton {
    public:
        sf::Image image_;

        Color color_ = Color::BLACK;
        unsigned size_ = 5;
    public:
        Tool(unsigned x, unsigned y, const char* image):
            AbstractButton(x, y),
            image_()
            {
                image_.loadFromFile(image);
            }
        ~Tool() {}

        virtual void actionWithCanvas(sf::VertexArray&,
                                      unsigned, unsigned, unsigned, unsigned,
                                      unsigned, unsigned) {}
};

#endif // TOOL_HPP_
