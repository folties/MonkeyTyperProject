#include "Logic.h"

Logic::Logic() :
    window(sf::VideoMode::getDesktopMode(), "MonkeyTyper"),
    currentState(GameState::PREVIEW),
    previewScreen(window.getSize())
{

}

auto Logic::run() -> void {
    while (window.isOpen()) {
        processEvent();
        float deltaTime = clock.restart().asSeconds();

        if (currentState == GameState::PREVIEW) {
            renderPreview();
        }
    }
}

auto Logic::processEvent() -> void {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

auto Logic::renderPreview() -> void {
    window.clear(sf::Color::Black);
    previewScreen.render(window);
    window.display();
}
