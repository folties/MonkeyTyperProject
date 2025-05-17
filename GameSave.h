#ifndef GAMESAVER_H
#define GAMESAVER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class GameSave {
public:
    struct WordState {
        std::string text;
        float posX;
        float posY;
        float speed;
    };

    struct GameState {
        float totalTime = 0.0f;
        int totalWords = 0;
        int score = 0;
        int missedWords = 0;

        std::vector<WordState> words;
    };

    static void saveGame(const GameState& state);
    static GameState loadGame();
    static bool isSaveAvailable();
    static void deleteSave();

private:
    static const std::string saveFile;
};

#endif // GAMESAVER_H
