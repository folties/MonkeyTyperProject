#include "GameSave.h"

const std::string GameSave::saveFile = "../materials/saves/savegame.txt";

void GameSave::saveGame(const GameState& state) {
    std::ofstream outFile(saveFile);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open save file for writing.\n";
        return;
    }

    outFile << state.topic          << "\n";
    outFile << state.fontName       << "\n";
    outFile << state.difficultyLevel<< "\n";

    outFile << state.totalTime << "\n";
    outFile << state.wordsClaimed << "\n";
    outFile << state.score << "\n";
    outFile << state.missedWords << "\n";

    outFile << state.words.size() << "\n";
    for (auto& word : state.words) {
        outFile << word.text << "\n";
        outFile << word.posX << " " << word.posY << " " << word.speed << "\n";
    }

    outFile.close();
}

GameSave::GameState GameSave::loadGame() {
    GameState state;
    std::ifstream inFile(saveFile);

    if (!inFile.is_open()) {
        std::cerr << "No save file found.\n";
    }

    inFile >> state.topic;
    inFile >> state.fontName;
    inFile >> state.difficultyLevel;

    inFile >> state.totalTime;
    inFile >> state.wordsClaimed;
    inFile >> state.score;
    inFile >> state.missedWords;

    int wordCount;
    inFile >> wordCount;

    for (int i = 0; i < wordCount; ++i) {
        WordState word;
        inFile >> word.text; //
        inFile >> word.posX >> word.posY >> word.speed;
        state.words.push_back(word);
    }

    inFile.close();
    return state;
}

bool GameSave::isSaveAvailable() {
    std::ifstream inFile(saveFile);
    return inFile.good();
}


