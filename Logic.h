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

enum class GameState {
    PREVIEW,
    PLAYING,
    GAME_OVER
};

class Logic {
public:
    Logic();

    auto run() -> void;
    auto renderPreview() -> void;

private:
    auto processEvents() -> void;
    auto update(float deltaTime) -> void;
    auto render() -> void;
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

    GameState currentState;

    Background background;
    Word word;
    Typing typing;
    Panel panel;
    GameEnd gameEnd;
    Shortcut shortcut;
    Resources resources;
    Preview previewScreen;
    sf::Music music;

    Scores scores;
    Instruction instruction;
    GameMenu gameMenu;

    float totalTime;
    float wpm;
    float missed;
    bool gameStarted;
    float countdownTime;
    sf::Text countdownText;
};

#endif //LOGIC_H
