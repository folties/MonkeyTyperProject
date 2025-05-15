
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "SFML/Graphics/Text.hpp"
#include "Resources.h"

#pragma once


class Instruction {
public:
    Instruction(const sf::Font& font, const sf::Vector2u& windowSize);
    auto setVisible(bool visible) -> void;
    auto isVisible() -> bool;
    auto handleClick(const sf::Vector2f &mousePos) -> void;
    auto render(sf::RenderWindow &window) -> void;

private:
    sf::RectangleShape instructionPanel;
    bool instructionVisible = false;

    sf::Text instructionText;
    sf::Text informationText;
    sf::Text pauseShortcutText;
    sf::Text movementShortcutText;
    sf::Text musicShortcutText;
    sf::Text soundShortcutText;
    sf::Text wishesText;
    sf::Text closeButton;

    void setupElements(const sf::Vector2u& windowSize);
};


#endif //INSTRUCTION_H
