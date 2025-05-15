//
// Created by MSI on 21.04.2025.
//

#include "Shortcut.h"

auto Shortcut::handleKeyEvent(const sf::Event::KeyPressed& event, Typing& typing, Word& word, Panel& panel, Resources& resources, GameMenu& gameMenu) -> void{
    if (event.scancode == sf::Keyboard::Scancode::Escape) {
        resources.backgroundMusic.stop();
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
            sf::Music& music = resources.getMusic();
            if (music.getStatus() == sf::SoundSource::Status::Playing){
                music.pause();
            } else {
                music.play();
            }
        }
        else if (event.scancode == sf::Keyboard::Scancode::Up) {
            typeSoundEnabled = !typeSoundEnabled;  // Toggle type sound state
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

