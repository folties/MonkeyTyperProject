#ifndef LOGIC_H
#define LOGIC_H

#pragma once

#include <SFML/Graphics.hpp>

#include "Preview.h"
#include "Resources.h"
#include "Background.h"

enum class GameState {
    PREVIEW,
    PLAYING,
    GAMEOVER
};

class Logic {
public:
    Logic();

    auto run() -> void;

private:
    Preview previewScreen;
    Resources resources;

    sf::RenderWindow window;
    sf::Clock clock;
    GameState currentState;


    auto processEvent() -> void;
    auto renderPreview() -> void;
};



#endif //LOGIC_H
