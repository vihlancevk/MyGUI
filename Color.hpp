#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <SFML/Graphics.hpp>

enum Color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 4,
    WHITE = 7
};

sf::Color calculateColor(Color color);

#endif // COLOR_HPP_
