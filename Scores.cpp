#include "Scores.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Scores::Scores(const sf::Font& font, const sf::Vector2u& windowSize) :
      titleText(font),
      closeButton(font)
{
    setupElements(windowSize);
}

auto Scores::setupElements(const sf::Vector2u &windowSize) -> void {
    panel.setSize(sf::Vector2f(windowSize.x * 0.7f, windowSize.y * 0.7f));
    panel.setFillColor(sf::Color(40, 40, 60, 250));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(3.f);
    panel.setOrigin(panel.getSize() / 2.f);
    panel.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    titleText.setString("Best Results");
    titleText.setCharacterSize(windowSize.y * 0.04f);
    titleText.setFillColor(sf::Color(120,190,255));
    titleText.setPosition(sf::Vector2f(panel.getPosition().x * 0.88f,  panel.getPosition().y * 0.3f));

    closeButton.setString("[X]");
    closeButton.setCharacterSize(windowSize.y * 0.03f);
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition(sf::Vector2f(panel.getPosition().x * 1.65f,  panel.getPosition().y * 0.3f));

    updateTexts();
}

auto Scores::loadFromFile() -> void {
    std::string filename = "../materials/history/bestResults.txt";
    bestScores.clear();
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        ScoreEntry entry;
        iss >> entry.note >> entry.difficulty >> entry.topic >> entry.wpm >> entry.missedWords >> entry.time;
        if (!entry.note.empty() && !entry.difficulty.empty())
            bestScores.push_back(entry);
    }
    std::sort(bestScores.begin(), bestScores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.wpm > b.wpm;
    });
    updateTexts();
}

auto Scores::render(sf::RenderWindow& window) -> void {
    if (visible) {
        window.draw(panel);
        window.draw(titleText);
        window.draw(closeButton);
        for (const auto& text : scoreTexts) {
            window.draw(text);
        }
    }
}

auto Scores::setVisible(bool v) -> void {
    visible = v;
}

auto Scores::isVisible()  -> bool {
    return visible;
}

auto Scores::handleClick(const sf::Vector2f& mousePos) -> void {
    if (visible && closeButton.getGlobalBounds().contains(mousePos)) {
        visible = false;
    }
}

auto Scores::setCurrentDifficulty(const std::string& diff) -> void {
    currentDifficulty = diff;
    updateTexts();
}

auto Scores::updateTexts() -> void {
    scoreTexts.clear();
    float y = panel.getPosition().y * 0.4f;
    size_t shown = 0;
    for (size_t i = 0; i < bestScores.size(); ++i) {
        const auto& entry = bestScores[i];
        if (shown < 15 && entry.difficulty == currentDifficulty){
            sf::Text text(titleText.getFont());
            text.setCharacterSize(panel.getSize().x * 0.02f);
            text.setFillColor(sf::Color::White);
            std::ostringstream oss;
            oss << shown+1 << ". [" << entry.topic << "] " << entry.note << "  WPM: " << entry.wpm << "  Missed: " << entry.missedWords << "  Time: " << static_cast<int>(entry.time) << "s";
            text.setString(oss.str());
            text.setPosition(sf::Vector2f(panel.getPosition().x * 0.35f, y));
            y += 40;
            scoreTexts.push_back(text);
            ++shown;
        }
    }
} 