#include "Instruction.h"

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
    closeButton.setCharacterSize(windowSize.y * 0.03f);
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 1.65f, instructionPanel.getPosition().y * 0.3f));

    instructionText.setString("Instruction");
    instructionText.setCharacterSize(windowSize.y * 0.04f);
    instructionText.setFillColor(sf::Color(120,190,255));
    instructionText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 0.88f, instructionPanel.getPosition().y * 0.3f));

    informationText.setString(">>Type the words moving left to right before they disappear!  "
                              "\n\n>>Improve your Words Per Minute (WPM) and avoid missing words to \nachieve a high score."
                              "\n\n>>Use the X symbols next to each option to switch between different \nfonts, topics, and difficulties.");
    informationText.setCharacterSize(windowSize.y * 0.03f);
    informationText.setFillColor(sf::Color::White);
    informationText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 0.4f, instructionPanel.getPosition().y * 0.5f));

    pauseShortcutText.setString("ESCAPE >> Open Menu Screen");
    pauseShortcutText.setCharacterSize(windowSize.y * 0.035f);
    pauseShortcutText.setFillColor(sf::Color::White);
    pauseShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 0.4f, instructionPanel.getPosition().y * 1.1f));

    movementShortcutText.setString("Right Shift >> Change Movement");
    movementShortcutText.setCharacterSize(windowSize.y * 0.035f);
    movementShortcutText.setFillColor(sf::Color::White);
    movementShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 0.4f, instructionPanel.getPosition().y * 1.3f));

    musicShortcutText.setString("Down Arrow >> Toggle Music ");
    musicShortcutText.setCharacterSize(windowSize.y * 0.035f);
    musicShortcutText.setFillColor(sf::Color::White);
    musicShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 1.1f,instructionPanel.getPosition().y * 1.1f));

    soundShortcutText.setString("Up Arrow >> Toggle Sound ");
    soundShortcutText.setCharacterSize(windowSize.y * 0.035f);
    soundShortcutText.setFillColor(sf::Color::White);
    soundShortcutText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 1.1f,instructionPanel.getPosition().y * 1.3f));

    wishesText.setString("HAVE A GOOD GAME!");
    wishesText.setCharacterSize(windowSize.y * 0.035f);
    wishesText.setFillColor(sf::Color(120, 190, 255));
    wishesText.setPosition(sf::Vector2f(instructionPanel.getPosition().x * 0.8f,instructionPanel.getPosition().y * 1.5f));
}

auto Instruction::render(sf::RenderWindow& window) -> void{
    if (!instructionVisible) {
        return;
    }
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

