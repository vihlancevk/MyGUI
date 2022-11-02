#ifndef TOOL_HPP_
#define TOOL_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

class Tool {
    public:
        unsigned size_;
        sf::Color color_;

        bool isActive_;
    public:
        Tool():
            size_(10),
            color_(sf::Color::Black),
            isActive_(false)
            {}

        virtual void actionWithCanvas(sf::VertexArray&,
                                      unsigned, unsigned, unsigned, unsigned,
                                      unsigned, unsigned) {}

        virtual ~Tool() = default;
};

#endif // TOOL_HPP_
