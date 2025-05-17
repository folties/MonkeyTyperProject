#ifndef WORD_H
#define WORD_H
#pragma once

#include <unordered_set>
#include <SFML/Graphics.hpp>

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD,
    INSANE
};

struct Words : sf::Text {

    Words(const std::string& str,
          const sf::Font& font,
          unsigned int size = 25,
          sf::Color color = sf::Color::White,
          sf::Vector2f pos = {0.f, 0.f})
        : sf::Text(font,str, size) // call base sf::Text constructor
    {
        setFillColor(color);
        setPosition(pos);
    }

    float speed;
};

class Word {
public:
    Word(const sf::Font &font);

    auto updateWords(float deltaTime, sf::Vector2u windowSize) -> void;
    auto drawWord(sf::RenderWindow &window) -> void;
    auto isGameOver() -> bool;
    auto toggleMovementMode() -> void;
    auto getTotalWords() -> int;
    auto getMissedWords() -> int;
    auto setFont(const sf::Font& font) -> void;

    auto getFont() -> sf::Font &;

    auto setDifficulty(Difficulty difficulty) -> void;
    void setText(const std::string& text);
    void setPosition(const sf::Vector2f& position);
    void setSpeed(float speed);
    void setMissedWords(int missed);
    int getMissedWords() const;
    auto stringToDifficulty(const std::string &str) -> Difficulty;
    auto setTopic(const std::string &topic) -> void;
    auto getTopic() -> std::string;
    std::string getText() const;
    float getSpeed() const;
    auto reset() -> void;
    auto initWords() -> void;
    auto getActiveWords() -> std::vector<Words>&;


private:

    std::vector<std::string> wordsList; //list of words
    std::vector<Words> objectsWords; //word objects that are display
    float wordSpawnTimer = 0.f;
    float wordSpawnInterval = 1.f; // spawn one word every 1 second
    size_t nextWordIndex = 0;      // next word to spawn
    std::unordered_set<int> usedYSteps; // tracks used y slots
    int missedWords = 0; // tracks how many words went off-screen
    sf::Font font;
    bool useStepMovement = true;  // default to smooth
    float stepTimer = 0.f;
    const float stepInterval = 0.3f; // controls how fast the step happens
    const float stepSize = 15.f;     // how far each jump is
    std::string selectedTopic = "Animals"; // default
    Difficulty selectedDifficulty = Difficulty::EASY; // default
    sf::Text wordText;  // Add this line
    float speed;        // Also add this line, it is missing


};



#endif //WORD_H
