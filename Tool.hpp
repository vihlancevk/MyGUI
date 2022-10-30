#ifndef TOOL_HPP_
#define TOOL_HPP_

#include <SFML/Graphics.hpp>

class Tool {
    public:
        bool isActive_;
    public:
        Tool():
            isActive_(false)
            {}

        virtual void actionWithCanvas(sf::VertexArray&,
                                      unsigned, unsigned, unsigned, unsigned,
                                      unsigned, unsigned) {
            std::cout << "Now active is StartTool\n";
        }

        virtual ~Tool() = default;
};

#endif // TOOL_HPP_
