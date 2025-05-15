#include "Background.h"
#include <random>
#include <fstream>
#include <iostream>
#include <unordered_set>

Background::Background(sf::Vector2u windowSize) {
    initStars(windowSize);
}

// Initialize stars with positions based on window size
auto Background::initStars(sf::Vector2u windowSize) -> void {
    std::mt19937 random(static_cast<unsigned>(time(0)));

    std::uniform_real_distribution<float> xDist(0.f, static_cast<float>(windowSize.x));
    std::uniform_real_distribution<float> yDist(0.f, static_cast<float>(windowSize.y));
    std::uniform_real_distribution<float> sizeDist(2.f, 4.f);
    std::uniform_real_distribution<float> speedDist(500.f, 700.f);

    for (int i = 0; i < 50; ++i) {
        Star star;
        star.shape.setRadius(sizeDist(random));
        star.shape.setFillColor(sf::Color::White);
        star.shape.setPosition(sf::Vector2f(xDist(random), yDist(random)));
        star.speed = speedDist(random);
        stars.push_back(star);
    }

    screenWidth = windowSize.x; // store for wraparound logic
}

auto Background::updateStars(float dt) -> void {
    for (auto& star : stars) {
        sf::Vector2f pos = star.shape.getPosition();
        pos.x += star.speed * dt;
        if (pos.x > screenWidth) pos.x = 0; // wraparound using current screen width
        star.shape.setPosition(pos);
    }
}

auto Background::drawStars(sf::RenderWindow& window) -> void {
    for (const auto& star : stars)
        window.draw(star.shape);
}