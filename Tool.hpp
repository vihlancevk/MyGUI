#ifndef TOOL_HPP_
#define TOOL_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Tool {
    public:
        unsigned size_;
        sf::Color color_;
    public:
        Tool(unsigned size = 10, sf::Color color = sf::Color::Black):
            size_(size),
            color_(color)
            {}

        virtual void actionWithCanvas(sf::VertexArray&,
                                      unsigned, unsigned, unsigned, unsigned,
                                      unsigned, unsigned) {}

        virtual ~Tool() = default;
};

#endif // TOOL_HPP_
