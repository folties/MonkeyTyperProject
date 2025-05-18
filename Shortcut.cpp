#include "Shortcut.h"

auto Shortcut::handleKeyEvent(const sf::Event::KeyPressed& event, Typing& typing, Word& word, Panel& panel, Resources& resources) -> void{
    if (event.scancode == sf::Keyboard::Scancode::Escape) {
        isGameMenu = !isGameMenu;
    }
    else if (!isGameMenu) {
        if (event.scancode == sf::Keyboard::Scancode::Enter) {
            typing.trySubmit(word);
            panel.setTypedText(typing.getCurrentInput());
            panel.setWordCounter(typing.getWordCount());
        }
        else if (event.scancode == sf::Keyboard::Scancode::RShift) {
            word.toggleMovementMode();
        }
        else if (event.scancode == sf::Keyboard::Scancode::Down) {
            resources.switchMusic();
        }
        else if (event.scancode == sf::Keyboard::Scancode::Up) {
            typeSoundEnabled = !typeSoundEnabled;
        }
    }
}

auto Shortcut::getMenuGameState() -> bool  {
    return isGameMenu;
}

auto Shortcut::setMenuGameState(bool state) -> void {
    isGameMenu = state;
}

auto Shortcut::isTypeSoundEnabled() -> bool {
    return typeSoundEnabled;
}

