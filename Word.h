#ifndef WORD_H
#define WORD_H

#include <SFML/Graphics.hpp>

#pragma once

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD,
    INSANE
};

struct Words : sf::Text  {

    Words(const std::string& str,const sf::Font& font,int size,sf::Vector2f pos) : sf::Text(font)
    {
        setString(str);
        setFont(font);
        setCharacterSize(size);
        setFillColor(sf::Color::White);
        setPosition(pos);
    }
    float speed;
};

class Word {
public:
    Word(const sf::Font &font);

    auto updateWords(float deltaTime, sf::Vector2u windowSize) -> void;
    auto drawWord(sf::RenderWindow &window) -> void;
    auto getActiveWords() -> std::vector<Words>&;
    auto toggleMovementMode() -> void;
    auto stringToDifficulty(const std::string &str) -> Difficulty;
    auto isGameOver() -> bool;
    auto reset() -> void;

    auto setMissedWords(int missed) -> void;
    auto setFont(const sf::Font& font) -> void;
    auto setDifficulty(Difficulty difficulty) -> void;
    auto setTopic(const std::string &topic) -> void;

    auto getTopic() -> std::string;
    auto getMissedWords() -> int;
    auto getTotalWords() -> int;

private:
    auto initWords() -> void;

    sf::Font font;
    sf::Text wordText;
    Difficulty selectedDifficulty = Difficulty::EASY;
    std::vector<std::string> wordsList;
    std::vector<Words> objectsWords;
    std::string selectedTopic = "Animals";
    size_t nextWordIndex = 0;

    bool useStepMovement = true;
    float speed;
    float stepTimer = 0.f;
    float stepInterval = 0.3f;
    float wordSpawnTimer = 0.f;
    float wordSpawnInterval = 1.f;
    int missedWords = 0;
};



#endif //WORD_H
