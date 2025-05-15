//
// Created by Nazar Korcheniyk on 08.05.2025.
//

#include "Instruction.h"
#include "Resources.h"

Instruction::Instruction(const sf::Font& font, const sf::Vector2u& windowSize):
    instructionText(font),
    informationText(font),
    pauseShortcutText(font),
    movementShortcutText(font),
    musicShortcutText(font),
    soundShortcutText(font),
    wishesText(font),
    closeButton(font)
{
    setupElements(windowSize);
}

auto Instruction::setupElements(const sf::Vector2u &windowSize) -> void {
    instructionPanel.setSize(sf::Vector2f(windowSize.x * 0.7f, windowSize.y * 0.7f));
    instructionPanel.setFillColor(sf::Color(40, 40, 60, 250));
    instructionPanel.setOutlineColor(sf::Color::White);
    instructionPanel.setOutlineThickness(3.f);
    instructionPanel.setOrigin(instructionPanel.getSize() / 2.f);
    instructionPanel.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    closeButton.setString("[X]");
    closeButton.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.03f));
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition(sf::Vector2f(instructionPanel.getPosition().x + instructionPanel.getSize().x / 2.f - 50,
                                       instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 10));

    instructionText.setString("Instruction");
    instructionText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.04f));
    instructionText.setFillColor(sf::Color(120,190,255));
    instructionText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 420,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 10));

    informationText.setString(">>Type the words moving left to right before they disappear!  "
                              "\n\n>>Improve your Words Per Minute (WPM) and avoid missing words to achieve \na high score."
                              "\n\n>>Use the X symbols next to each option to switch between different \nfonts, topics, and difficulties.");
    informationText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.03f));
    informationText.setFillColor(sf::Color::White);
    informationText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 30,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 50));

    pauseShortcutText.setString("ESCAPE >> Open Menu Screen");
    pauseShortcutText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.035f));
    pauseShortcutText.setFillColor(sf::Color::White);
    pauseShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 30,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 300));

    movementShortcutText.setString("Right Shift >> Change Word Movement");
    movementShortcutText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.035f));
    movementShortcutText.setFillColor(sf::Color::White);
    movementShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 30,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 350));

    musicShortcutText.setString("Down Arrow >> Toggle Music ");
    musicShortcutText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.035f));
    musicShortcutText.setFillColor(sf::Color::White);
    musicShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 600,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 300));

    soundShortcutText.setString("Up Arrow >> Toggle Sound ");
    soundShortcutText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.035f));
    soundShortcutText.setFillColor(sf::Color::White);
    soundShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 600,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 350));

    wishesText.setString("HAVE A GOOD GAME!");
    wishesText.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.035f));
    wishesText.setFillColor(sf::Color(120, 190, 255));
    wishesText.setPosition(sf::Vector2f(instructionPanel.getPosition().x - instructionPanel.getSize().x / 2.f + 350,
                                     instructionPanel.getPosition().y - instructionPanel.getSize().y / 2.f + 450));
}

auto Instruction::render(sf::RenderWindow& window) -> void{
    if (!instructionVisible) return;
    window.draw(instructionPanel);
    window.draw(instructionText);
    window.draw(closeButton);
    window.draw(informationText);
    window.draw(pauseShortcutText);
    window.draw(movementShortcutText);
    window.draw(musicShortcutText);
    window.draw(soundShortcutText);
    window.draw(wishesText);
}


auto Instruction::setVisible(bool v) -> void {
    instructionVisible = v;
}

auto Instruction::isVisible() -> bool {
    return instructionVisible;
}

auto Instruction::handleClick(const sf::Vector2f& mousePos) -> void {
    if (!instructionVisible) return;
    if (closeButton.getGlobalBounds().contains(mousePos)) {
        instructionVisible = false;
    }
}

