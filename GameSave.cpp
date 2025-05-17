#include "GameSave.h"

const std::string GameSave::saveFile = "../materials/saves/savegame.txt";

void GameSave::saveGame(const GameState& state) {
    std::ofstream outFile(saveFile);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open save file for writing." << std::endl;
        return;
    }

    // Write main game state
    outFile << state.totalTime << std::endl;
    outFile << state.totalWords << std::endl;
    outFile << state.score << std::endl;
    outFile << state.missedWords << std::endl;

    // Write word states
    outFile << state.words.size() << std::endl;
    for (const auto& word : state.words) {
        outFile << word.text << std::endl;
        outFile << word.posX << " " << word.posY << " " << word.speed << std::endl;
    }

    outFile.close();
    std::cout << "Game saved successfully!" << std::endl;
}

GameSave::GameState GameSave::loadGame() {
    GameState state;
    std::ifstream inFile(saveFile);

    if (!inFile.is_open()) {
        throw std::runtime_error("No save file found.");
    }

    // Read main game state
    inFile >> state.totalTime;
    inFile >> state.totalWords;
    inFile >> state.score;
    inFile >> state.missedWords;

    // Read word states
    int wordCount;
    inFile >> wordCount;

    inFile.ignore(); // Clear newline character

    for (int i = 0; i < wordCount; ++i) {
        WordState word;
        std::getline(inFile, word.text); // Read word text
        inFile >> word.posX >> word.posY >> word.speed;
        inFile.ignore(); // Clear the newline character
        state.words.push_back(word);
    }

    inFile.close();
    std::cout << "Game loaded successfully!" << std::endl;
    return state;
}

bool GameSave::isSaveAvailable() {
    std::ifstream inFile(saveFile);
    return inFile.good();
}

void GameSave::deleteSave() {
    if (remove(saveFile.c_str()) == 0) {
        std::cout << "Save file deleted successfully." << std::endl;
    } else {
        std::cerr << "Failed to delete save file." << std::endl;
    }
}
