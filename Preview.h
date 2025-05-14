#ifndef PREVIEW_H
#define PREVIEW_H

#pragma once
#include "Resources.h"
#include "SFML/Graphics.hpp"

enum class Difficulty {
    EASY,
    MEDIUM,
    HRAD,
    INSANE
};

enum class Fonts {
    PIXEL,
    ALPHBETA,
    HEVILLA,
    STEVE,
    WARWORK,
    GROSAC
};

enum class Topic {
    ANIMALS,
    TECHNOLOGY,
    NATURE
};

class Preview {
public:
    Preview(const sf::Vector2u& windowSize);

    auto render(sf::RenderWindow& window) -> void;
    auto setupElements(const sf::Vector2u& windowSize) -> void;

private:
    Resources resource;
    sf::Font previewFont;

    sf::RectangleShape previewPanel;

    sf::RectangleShape startButton;
    sf::Text startText;

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
