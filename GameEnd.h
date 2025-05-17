#ifndef GAMEEND_H
#define GAMEEND_H

#include <SFML/Graphics.hpp>
#include <cstdint>

#pragma once

class GameEnd {
public:
    GameEnd(const sf::Font& font, const sf::Vector2u& windowSize);

    auto setupElements(const sf::Vector2u &windowSize) -> void;
    auto setMissedWords(int count) -> void;
    auto setWPM(float wpm) -> void;
    auto setTime(float time) -> void;
    auto setTypedText(const std::string& text) -> void;

    auto render(sf::RenderWindow& window) -> void;

    auto handleLabelInput(uint32_t unicode) -> void;
    auto saveResultToFile() -> bool;
    auto showConfirmation(bool success) -> void;
    auto clearLabelAndConfirmation() -> void;

    auto setDifficulty(const std::string& diff) -> void;
    auto setTopic(const std::string& topic) -> void;
    auto isResultSaved() -> bool;

    void updateButtons(const sf::Vector2u &windowSize);


    auto isReturnButtonClicked(const sf::Vector2f& mousePos) -> bool ;
    auto isSaveButtonClicked(const sf::Vector2f& mousePos) -> bool;

private:
    sf::RectangleShape returnButton;
    sf::RectangleShape saveButton;
    sf::RectangleShape labelBox;
    sf::Text gameOverText;
    sf::Text wpmText;
    sf::Text timeText;
    sf::Text missedText;
    sf::Text returnButtonText;
    sf::Text labelPromptText;
    sf::Text labelText;
    sf::Text saveButtonText;
    sf::Text confirmationText;
    std::string typedText;
    std::string difficulty;
    std::string topic;
    std::string labelInput;
    bool showConfirmationMsg = false;
    bool saveSuccess = false;
    bool resultSaved = false;
    int missedWords = 0;
    float wpm = 0;
    float time = 0;
};

#endif // GAMEEND_H