#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <SFML/Graphics.hpp>

#include "Panel.h"
#include "Resources.h"
#include "Typing.h"
#include "Word.h"

#pragma once


class Shortcut {
public:
    auto handleKeyEvent(const sf::Event::KeyPressed& event, Typing& typing, Word& word, Panel& panel, Resources& resources) -> void;
    auto getMenuGameState() -> bool ;
    auto setMenuGameState(bool state) -> void;
    auto isTypeSoundEnabled() -> bool;

private:
    bool isGameMenu = false;
    bool typeSoundEnabled = true;
};



#endif //SHORTCUT_H
