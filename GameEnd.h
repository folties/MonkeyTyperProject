#ifndef GAMEEND_H
#define GAMEEND_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdint>

class GameEnd {
public:
    GameEnd(const sf::Font& font);
    auto setMissedWords(int count) -> void;
    auto show(sf::RenderWindow& window) -> void;
    auto isReturnButtonClicked(const sf::Vector2f& mousePos) -> bool ;
    auto setWPM(float wpm) -> void;
    auto setTime(float time) -> void;
    auto setTypedText(const std::string& text) -> void;
    auto handleLabelInput(uint32_t unicode) -> void;
    auto isSaveButtonClicked(const sf::Vector2f& mousePos) -> bool;
    auto saveResultToFile() -> bool;
    auto showConfirmation(bool success) -> void;
    auto clearLabelAndConfirmation() -> void;
    auto setDifficulty(const std::string& diff) -> void;
    auto setTopic(const std::string& topic) -> void;
    auto isResultSaved() -> bool;

private:
    sf::Text gameOverText;
    sf::Text wpmText;
    sf::Text timeText;
    sf::Text missedText;
    sf::RectangleShape returnButton;
    sf::Text returnButtonText;
    int missedWords = 0;
    float wpm = 0;
    float time = 0;
    sf::RectangleShape labelBox;
    sf::Text labelPromptText;
    sf::Text labelText;
    std::string labelInput;
    sf::RectangleShape saveButton;
    sf::Text saveButtonText;
    sf::Text confirmationText;
    std::string typedText;
    bool showConfirmationMsg = false;
    bool saveSuccess = false;
    std::string difficulty;
    std::string topic;
    bool resultSaved = false;  // Track if result has been saved
};

#endif // GAMEEND_H