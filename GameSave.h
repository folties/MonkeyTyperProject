#ifndef GAMESAVER_H
#define GAMESAVER_H

#include <vector>
#include <string>

#pragma once

class WordState {
public:
     std::string text;
     float posX;
     float posY;
     float speed;
};

class GameState {
public:
     float totalTime = 0.0f;
     int wordsClaimed = 0;
     int score = 0;
     int missedWords = 0;

     std::string topic;
     std::string fontName;
     std::string difficultyLevel;

     std::vector<WordState> words;
     size_t nextWordIndex =0;
};


class GameSave {
public:

     static auto saveGame(const GameState& state) -> void;
     static auto loadGame() -> GameState;
     static auto isSaveAvailable() -> bool;
     auto clearSave() -> void;

private:
     static const std::string saveFile;
};

#endif // GAMESAVER_H
