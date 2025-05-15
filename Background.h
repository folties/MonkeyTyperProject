#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Star {
    sf::CircleShape shape;
    float speed;
};

class Background {
public:
    Background(sf::Vector2u windowSize); // updated constructor
    auto updateStars(float dt) -> void;
    auto drawStars(sf::RenderWindow& window) -> void;

private:
    std::vector<Star> stars;
    unsigned int screenWidth = 800;
    auto initStars(sf::Vector2u windowSize) -> void; // updated
};

#endif