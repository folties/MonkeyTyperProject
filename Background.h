#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>


#pragma once

struct Star {
    sf::CircleShape shape;
    float speed;
};

class Background {
public:
    Background(sf::Vector2u windowSize);
    auto updateStars(float dt, const sf::Vector2u& windowSize) -> void;
    auto drawStars(sf::RenderWindow& window) -> void;

private:
    std::vector<Star> stars;
    auto initStars(sf::Vector2u windowSize) -> void;
};

#endif