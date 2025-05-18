#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <SFML/Graphics.hpp>

#pragma once

class GameMenu {
public:
    GameMenu(const sf::Font& font, const sf::Vector2u& windowSize);

    auto render(sf::RenderWindow& window) -> void;

    auto isResumeClicked(const sf::Vector2f& mousePos) -> bool;
    auto isLeaveClicked(const sf::Vector2f& mousePos) -> bool;

private:
    auto setupElements(const sf::Vector2u &windowSize) -> void;

    sf::RectangleShape panel;
    sf::Text titleText;
    sf::RectangleShape resumeButton;
    sf::Text resumeText;
    sf::RectangleShape leaveButton;
    sf::Text leaveText;
};

#endif // GAME_MENU_H 