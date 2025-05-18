
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "SFML/Graphics.hpp"

#pragma once

class Instruction {
public:
    Instruction(const sf::Font& font, const sf::Vector2u& windowSize);

    auto render(sf::RenderWindow &window) -> void;
    auto handleClick(const sf::Vector2f &mousePos) -> void;

    auto setVisible(bool visible) -> void;
    auto isVisible() -> bool;

private:

    auto setupElements(const sf::Vector2u& windowSize) -> void;

    sf::RectangleShape instructionPanel;

    sf::Text instructionText;
    sf::Text informationText;
    sf::Text pauseShortcutText;
    sf::Text movementShortcutText;
    sf::Text musicShortcutText;
    sf::Text soundShortcutText;
    sf::Text wishesText;
    sf::Text closeButton;

    bool instructionVisible = false;
};


#endif //INSTRUCTION_H
