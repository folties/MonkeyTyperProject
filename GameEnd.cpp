#include "GameEnd.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm>

GameEnd::GameEnd(const sf::Font& font)
    : gameOverText(font, "GAME OVER", 60),
      wpmText(font, "", 30),
      timeText(font, "", 30),
      missedText(font, "", 30),
      returnButtonText(font, "return to menu", 30),
      labelPromptText(font, "label your run", 28),
      labelText(font, "", 28),
      saveButtonText(font, "save result", 30),
      confirmationText(font, "", 28)
{
    gameOverText.setFillColor(sf::Color::White);
    wpmText.setFillColor(sf::Color::White);
    timeText.setFillColor(sf::Color::White);
    missedText.setFillColor(sf::Color::White);
    returnButtonText.setFillColor(sf::Color::White);
    saveButtonText.setFillColor(sf::Color::White);

    returnButton.setSize(sf::Vector2f(400.f, 100.f));
    returnButton.setFillColor(sf::Color(90, 60, 90));
    returnButton.setOutlineColor(sf::Color::White);
    returnButton.setOutlineThickness(6.f);

    // Label box
    labelBox.setSize(sf::Vector2f(400.f, 50.f));
    labelBox.setFillColor(sf::Color(220, 220, 220));
    labelBox.setOutlineColor(sf::Color::Black);
    labelBox.setOutlineThickness(3.f);

    labelPromptText.setFillColor(sf::Color::White);
    labelText.setFillColor(sf::Color::Black);

    // Save button
    saveButton.setSize(sf::Vector2f(220.f, 60.f));
    saveButton.setFillColor(sf::Color(90, 120, 180));
    saveButton.setOutlineColor(sf::Color::White);
    saveButton.setOutlineThickness(5.f);

    confirmationText.setFillColor(sf::Color::Yellow);
}

void GameEnd::setMissedWords(int count) {
    missedWords = count;
    missedText.setString("missed " + std::to_string(missedWords));
}

void GameEnd::setWPM(float wpmValue) {
    wpm = wpmValue;
    wpmText.setString("wpm " + std::to_string(wpm));
}

void GameEnd::setTime(float timeValue) {
    time = timeValue;
    timeText.setString("time " + std::to_string(time) + "s");
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
    if (resultSaved) return false;  // Don't save if already saved
    
    std::string filename = "../materials/history/bestResults.txt";
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) return false;
    std::string safeLabel = labelInput;
    std::replace(safeLabel.begin(), safeLabel.end(), ' ', '_');
    file << safeLabel << " " << difficulty << " " << topic << " " << static_cast<int>(wpm) << " " << missedWords << " " << static_cast<int>(time) << "\n";
    file.close();
    resultSaved = true;  // Mark as saved
    return true;
}

void GameEnd::showConfirmation(bool success) {
    showConfirmationMsg = true;
    saveSuccess = success;
    if (success) confirmationText.setString("result saved");
    else confirmationText.setString("failed to save result");
}

void GameEnd::show(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    sf::Vector2u size = window.getSize();

    // Title text
    gameOverText.setCharacterSize(static_cast<unsigned int>(size.y * 0.1f));
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(sf::Vector2f(gameOverBounds.size.x / 2.f, gameOverBounds.size.y / 2.f));
    gameOverText.setPosition(sf::Vector2f(static_cast<float>(size.x) / 2.f, size.y * 0.25f));


    // WPM text
    wpmText.setCharacterSize(static_cast<unsigned int>(size.y * 0.03f));
    sf::FloatRect wpmBounds = wpmText.getLocalBounds();
    wpmText.setOrigin(sf::Vector2f(wpmBounds.size.x / 2.f, wpmBounds.size.y / 2.f));
    wpmText.setPosition(sf::Vector2f(static_cast<float>(size.x) / 1.7f, size.y * 0.35f));

    // Time text
    timeText.setCharacterSize(static_cast<unsigned int>(size.y * 0.03f));
    sf::FloatRect timeBounds = timeText.getLocalBounds();
    timeText.setOrigin(sf::Vector2f(timeBounds.size.x / 2.f, timeBounds.size.y / 2.f));
    timeText.setPosition(sf::Vector2f(static_cast<float>(size.x) / 2.5f, size.y * 0.35f));

    missedText.setCharacterSize(static_cast<unsigned int>(size.y * 0.03f));
    sf::FloatRect missedBounds = missedText.getLocalBounds();
    missedText.setOrigin(sf::Vector2f(missedBounds.size.x / 2.f, missedBounds.size.y / 2.f));
    missedText.setPosition(sf::Vector2f(static_cast<float>(size.x) / 2.f, size.y * 0.35f));

    // Position label box and prompt (higher up)
    sf::FloatRect promptBounds = labelPromptText.getLocalBounds();
    labelPromptText.setOrigin(sf::Vector2f(promptBounds.size.x/2.f, promptBounds.size.y/2.f));
    labelPromptText.setPosition(sf::Vector2f(window.getSize().x/2.f, window.getSize().y*0.55f));

    labelBox.setOrigin(sf::Vector2f(labelBox.getSize().x/2.f, labelBox.getSize().y/2.f));
    labelBox.setPosition(sf::Vector2f(window.getSize().x/2.f, window.getSize().y*0.62f));

    sf::FloatRect labelBounds = labelText.getLocalBounds();
    labelText.setOrigin(sf::Vector2f(labelBounds.size.x/2.f, labelBounds.size.y/2.f));
    labelText.setPosition(labelBox.getPosition());

    // Save button (just below label box)
    saveButton.setOrigin(sf::Vector2f(saveButton.getSize().x/2.f, saveButton.getSize().y/2.f));
    saveButton.setPosition(sf::Vector2f(window.getSize().x/2.f, window.getSize().y*0.70f));
    sf::FloatRect saveBtnBounds = saveButtonText.getLocalBounds();
    saveButtonText.setOrigin(sf::Vector2f(saveBtnBounds.size.x/2.f, saveBtnBounds.size.y/2.f));
    saveButtonText.setPosition(saveButton.getPosition());

    // Change save button appearance if result is already saved
    if (resultSaved) {
        saveButton.setFillColor(sf::Color(100, 100, 100));  // Gray out the button
        saveButtonText.setString("saved");  // Change text
    } else {
        saveButton.setFillColor(sf::Color(90, 120, 180));  // Normal color
        saveButtonText.setString("save result");  // Normal text
    }

    // Return button at the bottom
    returnButton.setOrigin(sf::Vector2f(returnButton.getSize().x / 2.f, returnButton.getSize().y / 2.f));
    returnButton.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f, window.getSize().y * 0.88f));
    sf::FloatRect buttonTextBounds = returnButtonText.getLocalBounds();
    returnButtonText.setOrigin(sf::Vector2f(buttonTextBounds.size.x / 2.f, buttonTextBounds.size.y / 2.f));
    returnButtonText.setPosition(returnButton.getPosition());

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
    resultSaved = false;  // Reset save state
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