#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <SFML/Graphics.hpp>

#include "GameMenu.h"
#include "Panel.h"
#include "Resources.h"
#include "Typing.h"
#include "Word.h"

#pragma once


class Shortcut {
public:

    auto handleKeyEvent(const sf::Event::KeyPressed& event, Typing& typing, Word& word, Panel& panel, Resources& resources, GameMenu& gameMenu) -> void;
    auto getMenuGameState() -> bool ;
    auto setMenuGameState(bool state) -> void;
    auto drawMenuGame(sf::RenderWindow& window) -> void;
    auto isTypeSoundEnabled() -> bool;

private:
    bool isGameMenu = false;
    bool typeSoundEnabled = true;
};



#endif //SHORTCUT_H
