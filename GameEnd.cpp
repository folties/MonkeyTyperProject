#include "GameEnd.h"
#include <fstream>

GameEnd::GameEnd(const sf::Font& font, const sf::Vector2u& windowSize)
    : gameOverText(font),
      wpmText(font),
      timeText(font),
      missedText(font),
      returnButtonText(font),
      labelPromptText(font),
      labelText(font),
      saveButtonText(font)
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
}

auto GameEnd::setMissedWords(int count) -> void {
    missedWords = count;
    missedText.setString("missed " + std::to_string(missedWords));
}

auto GameEnd::setWPM(float wpmValue) -> void {
    wpm = wpmValue;
    wpmText.setString("wpm " + std::to_string(static_cast<int>(wpm)));
}

auto GameEnd::setTime(float timeValue) -> void {
    time = timeValue;
    timeText.setString("time " + std::to_string(static_cast<int>(time)) + "s");
}

auto GameEnd::setTypedText(const std::string& text) -> void {
    typedText = text;
}

auto GameEnd::handleLabelInput(uint32_t unicode) -> void{
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

auto GameEnd::isReturnButtonClicked(const sf::Vector2f& mousePos) -> bool {
    return returnButton.getGlobalBounds().contains(mousePos);
}

auto GameEnd::isSaveButtonClicked(const sf::Vector2f& mousePos) -> bool  {
    return saveButton.getGlobalBounds().contains(mousePos);
}

auto GameEnd::saveResultToFile() -> bool {
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
    resultSaved = true;
    return resultSaved;
}

auto GameEnd::updateButtons(const sf::Vector2u &windowSize) -> void {
    if (!resultSaved) {
        saveButton.setFillColor(sf::Color(90, 120, 180));
        saveButtonText.setString("save result");
        saveButtonText.setPosition(sf::Vector2f(windowSize.x * 0.455f, windowSize.y * 0.685));
    } else {
        saveButton.setFillColor(sf::Color(100, 100, 100));
        saveButtonText.setString("saved");
        saveButtonText.setPosition(sf::Vector2f(windowSize.x * 0.48f, windowSize.y * 0.685));

    }
}

auto GameEnd::render(sf::RenderWindow& window) -> void {
    updateButtons(window.getSize());

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
}

auto GameEnd::clearLabelAndConfirmation() -> void {
    labelInput.clear();
    labelText.setString("");
    resultSaved = false;
}

auto GameEnd::setDifficulty(const std::string& diff) -> void {
    difficulty = diff;
}

auto GameEnd::setTopic(const std::string& top) -> void {
    topic = top;
}

auto GameEnd::isResultSaved() -> bool {
    return resultSaved;
}

