#include "Background.h"

#include <random>

Background::Background(sf::Vector2u windowSize) {
    initStars(windowSize);
}

auto Background::initStars(sf::Vector2u windowSize) -> void {
    auto rand = std::mt19937(static_cast<unsigned>(time(0)));

    std::uniform_real_distribution<float> size(2.f, 4.f);
    std::uniform_real_distribution<float> speed(500.f, 700.f);
    std::uniform_real_distribution<float> x(0.f, static_cast<float>(windowSize.x));
    std::uniform_real_distribution<float> y(0.f, static_cast<float>(windowSize.y));

    for (int i = 0; i < 50; i++) {
        Star star;
        star.speed = speed(rand);
        star.starShape.setRadius(size(rand));
        star.starShape.setFillColor(sf::Color(100,100,100));
        star.starShape.setPosition(sf::Vector2f(x(rand), y(rand)));
        stars.push_back(star);
    }

}

auto Background::updateStars(float deltaTime, sf::Vector2u windowSize) -> void {
    for (auto& star : stars) {
        sf::Vector2f position = star.starShape.getPosition();
        position.x += star.speed * deltaTime;
        if (position.x > windowSize.x) {
            position.x = 0;
            star.starShape.setPosition(position);
        }
    }
}

auto Background::drawStars(sf::RenderWindow& window) -> void {
    for (auto& star : stars) {
        window.draw(star.starShape);
    }
}


