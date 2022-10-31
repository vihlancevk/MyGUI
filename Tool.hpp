#ifndef TOOL_HPP_
#define TOOL_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Color.hpp"

class Tool {
    public:
        unsigned size_;
        Color color_;

        bool isActive_;
    public:
        Tool():
            size_(10),
            color_(Color::BLACK),
            isActive_(false)
            {}

        virtual void actionWithCanvas(sf::VertexArray&,
                                      unsigned, unsigned, unsigned, unsigned,
                                      unsigned, unsigned) {
            std::cout << "Now active is Tool::actionWithCanvas\n";
        }

        virtual ~Tool() = default;
};

#endif // TOOL_HPP_
