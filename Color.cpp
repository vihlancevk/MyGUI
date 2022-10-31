#include "Color.hpp"

sf::Color calculateColor(Color color) {
    sf::Color sfColor
    (
        (sf::Uint8) ((color & 1) * 255),
        (sf::Uint8) (((color & 2) >> 1) * 255),
        (sf::Uint8) (((color & 4) >> 2) * 255)
    );

    return sfColor;
}
