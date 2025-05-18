#ifndef LOGIC_H
#define LOGIC_H

#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Word.h"
#include "Typing.h"
#include "Panel.h"
#include "GameEnd.h"
#include "Preview.h"
#include "Shortcut.h"
#include "Scores.h"
#include "Instruction.h"
#include "GameMenu.h"
#include "GameSave.h"

#pragma once

enum class GameStatus {
    PREVIEW,
    PLAYING,
    GAME_OVER
};

class Logic {
public:
    Logic();

    auto run() -> void;

private:
    auto renderPreview() -> void;
    auto processEvents() -> void;
    auto handleTextInput(uint32_t unicode) -> void;
    auto handlePreviewMouse(const sf::Vector2f &mousePos) -> void;
    auto onContinue() -> void;
    auto onStart() -> void;
    auto handlePlayingMouse(const sf::Vector2f &mousePos) -> void;
    auto handleMenuActions(const sf::Vector2f &mousePos) -> void;
    auto handleGameOverActions(const sf::Vector2f &mousePos) -> void;
    auto resumeGame() -> void;
    auto exitToPreview() -> void;
    auto applyLoadedState(const GameState &s) -> void;
    auto saveAndExitToPreview() -> void;
    auto applyFont(const std::string &fontName) -> void;
    auto applyDifficulty(const std::string &diff) -> void;
    auto applyTopic(const std::string &topic) -> void;
    auto update(float deltaTime) -> void;
    auto renderGame() -> void;
    auto initResources() -> void;
    auto initUI() -> void;
    auto handleInput(const sf::Event& event) -> void;
    auto startCountdown(float deltaTime) -> void;
    auto updateStats() -> void;
    auto handleScoresPanel(const sf::Event& event) -> void;
    auto resetGame() -> void;
    auto countVisibleWords() -> int;

    sf::RenderWindow window;
    sf::Font pixelFont;
    sf::Font bloxFont;
    sf::Clock clock;
    sf::Music music;
    sf::Text countdownText;

    GameStatus currentStatus;
    Background background;
    Word word;
    Typing typing;
    Panel panel;
    GameEnd gameEnd;
    Shortcut shortcut;
    Resources resources;
    Preview previewScreen;
    Scores scores;
    Instruction instruction;
    GameMenu gameMenu;
    GameSave saver;

    bool gameStarted;
    float totalTime;
    float wpm;
    float missed;
    float countdownTime;

};

#endif //LOGIC_H
