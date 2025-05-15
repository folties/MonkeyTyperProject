#include "Panel.h"
#include "fmt/compile.h"

Panel::Panel(const sf::Font& font, const sf::Vector2u& windowSize) :
    typedDisplay(font),
    wordCounterText(font),
    timerText(font),
    wpmText(font),
    trafficText(font),
    missedWordsText(font)
{
    setupElements(windowSize);
}

auto Panel::setupElements(const sf::Vector2u &windowSize) -> void {
    panelBackground.setSize(sf::Vector2f(windowSize.x, windowSize.y * 0.08f)); // 8% of height
    panelBackground.setPosition(sf::Vector2f(0, windowSize.y - panelBackground.getSize().y));
    panelBackground.setFillColor(sf::Color(0, 0, 100)); // light blue

    typedDisplay.setCharacterSize(windowSize.y * 0.03f);
    typedDisplay.setFillColor(sf::Color::White);
    typedDisplay.setPosition(sf::Vector2f(windowSize.x * 0.44f, windowSize.y * 0.927f));

    wordCounterText.setCharacterSize(windowSize.y * 0.022f);
    wordCounterText.setFillColor(sf::Color::White);
    wordCounterText.setPosition(sf::Vector2f(windowSize.x * 0.03f, windowSize.y * 0.920));

    timerText.setCharacterSize(windowSize.y * 0.022f);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(sf::Vector2f(windowSize.x * 0.9f, windowSize.y * 0.920));

    wpmText.setCharacterSize(windowSize.y * 0.022f);
    wpmText.setFillColor(sf::Color::White);
    wpmText.setPosition(sf::Vector2f(windowSize.x * 0.9f, windowSize.y * 0.950));

    trafficText.setCharacterSize(windowSize.y * 0.022f);
    trafficText.setFillColor(sf::Color::White);
    trafficText.setPosition(sf::Vector2f(windowSize.x * 0.15f, windowSize.y * 0.940));

    missedWordsText.setCharacterSize(windowSize.y * 0.022f);
    missedWordsText.setFillColor(sf::Color::White);
    missedWordsText.setPosition(sf::Vector2f(windowSize.x * 0.03f, windowSize.y * 0.950));
}

auto Panel::setTypedText(const std::string& text) -> void {
    typedDisplay.setString(text);
}

auto Panel::setWordCounter(int counter) -> void {
    wordCounterText.setString("Words claimed: " + std::to_string(counter));
}

auto Panel::setTimer(float seconds) -> void {
    timerText.setString("Time: " + std::to_string(static_cast<int>(seconds)) + "s");
}

auto Panel::setWPM(float wpm) -> void {
    wpmText.setString("WPM: " + std::to_string(static_cast<int>(wpm)));
}

auto Panel::setTraffic(int activeWords, int totalWords) -> void {
    trafficText.setString("Traffic: " + std::to_string(activeWords) + "/" + std::to_string(totalWords));
}

auto Panel::setMissedWords(int missedWords) -> void {
    missedWordsText.setString("Missed words: " + std::to_string(missedWords));
}

auto Panel::reset()-> void {
    setTypedText("");
    setWordCounter(0);
    setTimer(0.f);
    setWPM(0.f);
    setTraffic(0, 0);
    setMissedWords(0);
}

auto Panel::draw(sf::RenderWindow& window) -> void {
    window.draw(panelBackground);
    window.draw(typedDisplay);
    window.draw(wordCounterText);
    window.draw(timerText);
    window.draw(wpmText);
    window.draw(trafficText);
    window.draw(missedWordsText);
}