#ifndef BACKGROUND_H
#define BACKGROUND_H

#pragma once

#include "SFML/Graphics.hpp"


class Star {
public:
    sf::CircleShape starShape;
    float speed;
};

class Background {
    public:
    Background(sf::Vector2u windowSize);

    auto updateStars(float deltaTime, sf::Vector2u windowSize) -> void;
    auto drawStars(sf::RenderWindow& window) -> void;
    auto initStars(sf::Vector2u windowSize) -> void;

    private:
    std::vector<Star> stars;


};



#endif //BACKGROUND_H
