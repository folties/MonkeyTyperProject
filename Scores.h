#ifndef SCORES_H
#define SCORES_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#pragma once

struct ScoreEntry {
    std::string note;
    std::string difficulty;
    std::string topic;
    int wpm;
    int missedWords;
    float time;
};

class Scores {
public:
    Scores(const sf::Font& font, const sf::Vector2u& windowSize);

    auto render(sf::RenderWindow& window) -> void;
    auto handleClick(const sf::Vector2f& mousePos) -> void;
    auto loadFromFile() -> void;

    auto isVisible() -> bool;
    auto setVisible(bool visible) -> void;
    auto setCurrentDifficulty(const std::string& diff) -> void;


private:
    auto setupElements(const sf::Vector2u &windowSize) -> void;
    auto updateTexts() -> void;


    sf::RectangleShape panel;
    sf::Text titleText;
    sf::Text closeButton;
    std::vector<sf::Text> scoreTexts;
    std::vector<ScoreEntry> bestScores;
    std::string currentDifficulty;
    bool visible = false;
};

#endif // SCORES_H 