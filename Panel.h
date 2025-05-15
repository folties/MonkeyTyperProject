#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>
#include <string>

#pragma once

class Panel {
public:
    Panel(const sf::Font& font, const sf::Vector2u& windowSize);

    auto setupElements(const sf::Vector2u &windowSize) -> void;

    auto setTypedText(const std::string& text) -> void;
    auto draw(sf::RenderWindow& window) -> void;
    auto setWordCounter(int counter) -> void;
    auto setTimer(float seconds) -> void;
    auto setWPM(float wpm) -> void;
    auto setTraffic(int activeWords, int totalWords) -> void;
    auto setMissedWords(int missedWords) -> void;
    auto reset() -> void;

private:
    sf::RectangleShape panelBackground;
    sf::Text typedDisplay;
    sf::Text wordCounterText;
    sf::Text timerText;
    sf::Text wpmText;
    sf::Text trafficText;
    sf::Text missedWordsText;
};

#endif // PANEL_H