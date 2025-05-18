#ifndef PREVIEW_H
#define PREVIEW_H

#include "Resources.h"
#include "SFML/Graphics.hpp"

#pragma once

class Preview {
public:
    Preview(const sf::Vector2u& windowSize);

    auto render(sf::RenderWindow& window) -> void;
    auto processMouseClick(const sf::Vector2f &mousePos) -> void;

    auto getSelectedFontName() -> std::string;
    auto getSelectedDifficulty() -> std::string;
    auto getSelectedTopicName() -> std::string;

    auto isStartButtonClicked(const sf::Vector2f &mousePos) -> bool;
    auto isScoresButtonClicked(const sf::Vector2f &mousePos) -> bool;
    auto isInstructionButtonClicked(const sf::Vector2f &mousePos) -> bool;
    bool isContinueButtonClicked(const sf::Vector2f& mousePos) const;
private:
    auto updateButtons() -> void;
    auto centerText(sf::Text &text, sf::Vector2f center) -> void;
    auto setupElements(const sf::Vector2u& windowSize) -> void;

    Resources resource;

    sf::Font previewFont;
    sf::RectangleShape previewPanel;

    sf::RectangleShape startButton;
    sf::Text startText;

    sf::RectangleShape continueButton;
    sf::Text continueText;

    sf::RectangleShape scoresButton;
    sf::Text scoresText;

    sf::RectangleShape instructionButton;
    sf::Text instructionText;

    sf::Text fontText;
    sf::Text fontValueText;
    sf::Text fontLeftArrow;
    sf::Text fontRightArrow;

    sf::Text difficultyText;
    sf::Text difficultyValueText;
    sf::Text difficultyLeftArrow;
    sf::Text difficultyRightArrow;

    sf::Text topicText;
    sf::Text topicValueText;
    sf::Text topicLeftArrow;
    sf::Text topicRightArrow;

    std::vector<std::string> fontOptions = {"Pixel", "Alphbeta", "Hevilla", "Steve", "Warwork", "Grosac"};
    std::vector<std::string> difficultyOptions = {"Easy", "Medium", "Hard", "Insane"};
    std::vector<std::string> topicOptions = {"Animals", "Technology", "Nature"};

    int fontIndex = 0;
    int difficultyIndex = 0;
    int topicIndex = 0;
};



#endif //PREVIEW_H