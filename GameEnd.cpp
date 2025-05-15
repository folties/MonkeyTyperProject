#include "GameEnd.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm>

GameEnd::GameEnd(const sf::Font& font, const sf::Vector2u& windowSize)
    : gameOverText(font),
      wpmText(font),
      timeText(font),
      missedText(font),
      returnButtonText(font),
      labelPromptText(font),
      labelText(font),
      saveButtonText(font),
      confirmationText(font)
{
    setupElements(windowSize);
}

auto GameEnd::setupElements(const sf::Vector2u &windowSize) -> void {

    gameOverText.setString("GAME OVER");
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setCharacterSize(windowSize.y * 0.1f);
    gameOverText.setPosition(sf::Vector2f(windowSize.x * 0.37f, windowSize.y * 0.2f));

    auto setupText = [&](sf::Text &text, const std::string& string, sf::Vector2f position) -> void {
        text.setString(string);
        text.setCharacterSize(windowSize.y * 0.03);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);
    };

    setupText(wpmText, "", sf::Vector2f(windowSize.x * 0.35, windowSize.y * 0.35f));
    setupText(timeText, "", sf::Vector2f(windowSize.x * 0.47, windowSize.y * 0.35f));
    setupText(missedText, "", sf::Vector2f(windowSize.x * 0.59, windowSize.y * 0.35f));
    setupText(returnButtonText, "return to menu", sf::Vector2f(windowSize.x * 0.443f, windowSize.y * 0.87f));
    setupText(saveButtonText, "save result", sf::Vector2f(windowSize.x * 0.455f, windowSize.y * 0.685));
    setupText(labelPromptText, "label your run", sf::Vector2f(windowSize.x * 0.444f, windowSize.y * 0.55f));

    returnButton.setSize(sf::Vector2f(400.f, 100.f));
    returnButton.setFillColor(sf::Color(90, 60, 90));
    returnButton.setOutlineColor(sf::Color::White);
    returnButton.setOutlineThickness(6.f);
    returnButton.setOrigin(sf::Vector2f(returnButton.getSize().x / 2.f, returnButton.getSize().y / 2.f));
    returnButton.setPosition(sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.88f));

    labelBox.setSize(sf::Vector2f(400.f, 50.f));
    labelBox.setFillColor(sf::Color(220, 220, 220));
    labelBox.setOutlineColor(sf::Color::Black);
    labelBox.setOutlineThickness(3.f);
    labelBox.setOrigin(sf::Vector2f(labelBox.getSize().x/2.f, labelBox.getSize().y/2.f));
    labelBox.setPosition(sf::Vector2f(windowSize.x* 0.5f, windowSize.y * 0.62f));

    saveButton.setSize(sf::Vector2f(220.f, 60.f));
    saveButton.setFillColor(sf::Color(90, 120, 180));
    saveButton.setOutlineColor(sf::Color::White);
    saveButton.setOutlineThickness(5.f);
    saveButton.setOrigin(sf::Vector2f(saveButton.getSize().x/2.f, saveButton.getSize().y/2.f));
    saveButton.setPosition(sf::Vector2f(windowSize.x * 0.5, windowSize.y*0.70f));

    labelText.setPosition(sf::Vector2f(windowSize.x * 0.405f, windowSize.y * 0.605f));
    labelText.setFillColor(sf::Color::Black);

    if (resultSaved) {
        saveButton.setFillColor(sf::Color(100, 100, 100));
        saveButtonText.setString("saved");
    } else {
        saveButton.setFillColor(sf::Color(90, 120, 180));
        saveButtonText.setString("save result");
    }
    confirmationText.setFillColor(sf::Color::Yellow);
}

void GameEnd::setMissedWords(int count) {
    missedWords = count;
    missedText.setString("missed " + std::to_string(missedWords));
}

void GameEnd::setWPM(float wpmValue) {
    wpm = wpmValue;
    wpmText.setString("wpm " + std::to_string(static_cast<int>(wpm)));
}

void GameEnd::setTime(float timeValue) {
    time = timeValue;
    timeText.setString("time " + std::to_string(static_cast<int>(time)) + "s");
}

void GameEnd::setTypedText(const std::string& text) {
    typedText = text;
}

void GameEnd::handleLabelInput(uint32_t unicode) {
    if (unicode == 8) {
        if (!labelInput.empty()) labelInput.pop_back();
    } else if (unicode >= 32 && unicode <= 126) {
        std::string testInput = labelInput + static_cast<char>(unicode);
        labelText.setString(testInput);
        float boxWidth = labelBox.getSize().x - 40.f;
        sf::FloatRect bounds = labelText.getLocalBounds();
        if (bounds.size.x <= boxWidth) {
            labelInput = testInput;
        }
    }
    labelText.setString(labelInput);
}

bool GameEnd::isReturnButtonClicked(const sf::Vector2f& mousePos)  {
    return returnButton.getGlobalBounds().contains(mousePos);
}

bool GameEnd::isSaveButtonClicked(const sf::Vector2f& mousePos)  {
    return saveButton.getGlobalBounds().contains(mousePos);
}

bool GameEnd::saveResultToFile() {
    if (resultSaved) {
        return false;
    }
    std::string filename = "../materials/history/bestResults.txt";
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    std::string safeLabel = labelInput;
    std::replace(safeLabel.begin(), safeLabel.end(), ' ', '_');
    file << safeLabel << " " << difficulty << " " << topic << " " << static_cast<int>(wpm) << " " << missedWords << " " << static_cast<int>(time) << "\n";
    file.close();
    resultSaved = true;  // Mark as saved
    return resultSaved;
}

void GameEnd::showConfirmation(bool success) {
    showConfirmationMsg = true;
    saveSuccess = success;
    if (success) {
        confirmationText.setString("result saved");
    }
    else confirmationText.setString("failed to save result");
}



void GameEnd::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(gameOverText);
    window.draw(wpmText);
    window.draw(timeText);
    window.draw(missedText);
    window.draw(labelPromptText);
    window.draw(labelBox);
    window.draw(labelText);
    window.draw(saveButton);
    window.draw(saveButtonText);
    window.draw(returnButton);
    window.draw(returnButtonText);
    if (showConfirmationMsg) window.draw(confirmationText);
}

void GameEnd::clearLabelAndConfirmation() {
    labelInput.clear();
    labelText.setString("");
    showConfirmationMsg = false;
    confirmationText.setString("");
    resultSaved = false;
}

void GameEnd::setDifficulty(const std::string& diff) {
    difficulty = diff;
}

auto GameEnd::setTopic(const std::string& top) -> void {
    topic = top;
}

auto GameEnd::isResultSaved() -> bool {
    return resultSaved;
}