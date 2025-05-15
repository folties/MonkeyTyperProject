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

    auto setupElements(const sf::Vector2u &windowSize) -> void;

    auto isVisible() -> bool;

    auto loadFromFile() -> void;
    auto saveToFile(const std::string& filename) -> void;
    auto tryAddScore(const ScoreEntry& entry) -> void;
    auto render(sf::RenderWindow& window) -> void;
    auto setVisible(bool visible) -> void;
    auto handleClick(const sf::Vector2f& mousePos) -> void;
    auto setCurrentDifficulty(const std::string& diff) -> void;
    auto updateTexts() -> void;

private:
    std::vector<ScoreEntry> bestScores;
    sf::RectangleShape panel;
    sf::Text titleText;
    std::vector<sf::Text> scoreTexts;
    sf::Text closeButton;
    bool visible = false;
    std::string currentDifficulty;
};

#endif // SCORES_H 