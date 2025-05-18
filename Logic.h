#ifndef LOGIC_H
#define LOGIC_H

#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Word.h"
#include "Typing.h"
#include "Panel.h"
#include "Preview.h"
#include "Shortcut.h"
#include "Scores.h"
#include "Instruction.h"
#include "GameMenu.h"
#include "GameSave.h"
#include "GameEnd.h"
#include "Resources.h"

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
    auto initResources() -> void;
    auto initUI() -> void;

    auto renderPreview() -> void;
    auto renderGame() -> void;
    auto renderGameOver() -> void;

    auto onContinue() -> void;
    auto onStart() -> void;

    auto processEvents() -> void;
    auto update(float deltaTime) -> void;

    auto handleTextInput(uint32_t unicode) -> void;
    auto handlePreviewMouse(const sf::Vector2f &mousePos) -> void;
    auto handlePlayingMouse(const sf::Vector2f &mousePos) -> void;
    auto handleMenuActions(const sf::Vector2f &mousePos) -> void;
    auto handleGameOverActions(const sf::Vector2f &mousePos) -> void;

    auto applyLoadedState(const GameState &s) -> void;
    auto applyFont(const std::string &fontName) -> void;
    auto applyDifficulty(const std::string &diff) -> void;
    auto applyTopic(const std::string &topic) -> void;

    auto saveAndExitToPreview() -> void;
    auto exitToPreview() -> void;
    auto resetGame() -> void;
    auto resumeGame() -> void;
    auto startCountdown(float deltaTime) -> void;

    sf::RenderWindow window;
    sf::Font pixelFont;
    sf::Font bloxFont;
    sf::Clock clock;
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
