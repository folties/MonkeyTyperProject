#include "Preview.h"
#include "GameSave.h"

Preview::Preview(const sf::Vector2u& windowSize) :
    previewFont(resource.getFont("BloxFont")),
    startText(previewFont),
    continueText(previewFont),
    scoresText(previewFont),
    instructionText(previewFont),
    fontText(previewFont),
    fontValueText(previewFont),
    fontLeftArrow(previewFont),
    fontRightArrow(previewFont),
    difficultyText(previewFont),
    difficultyValueText(previewFont),
    difficultyLeftArrow(previewFont),
    difficultyRightArrow(previewFont),
    topicText(previewFont),
    topicValueText(previewFont),
    topicLeftArrow(previewFont),
    topicRightArrow(previewFont)
{
    setupElements(windowSize);
}

auto Preview::setupElements(const sf::Vector2u& windowSize) -> void {
    previewPanel.setSize(sf::Vector2f(windowSize.x * 0.7f , windowSize.y * 0.7f ));
    previewPanel.setFillColor(sf::Color(120, 120, 120));
    previewPanel.setOutlineColor(sf::Color(0,0,100));
    previewPanel.setOutlineThickness(5.f);
    previewPanel.setOrigin(previewPanel.getSize() / 2.f);
    previewPanel.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    auto setupButtons = [&](sf::RectangleShape &button, sf::Vector2f position) -> void {
        button.setSize(sf::Vector2f(windowSize.x * 0.15f, windowSize.y * 0.06f));
        button.setFillColor(sf::Color(0, 0, 90));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(3.f);
        button.setOrigin(button.getSize() / 2.f);
        button.setPosition(position);
    };

    setupButtons(startButton, sf::Vector2f(previewPanel.getPosition().x , previewPanel.getPosition().y * 0.9f));
    setupButtons(continueButton, sf::Vector2f(previewPanel.getPosition().x , previewPanel.getPosition().y * 1.1f));
    setupButtons(scoresButton, sf::Vector2f(previewPanel.getPosition().x, previewPanel.getPosition().y * 1.3f));
    setupButtons(instructionButton, sf::Vector2f(previewPanel.getPosition().x, previewPanel.getPosition().y * 1.5f));

    auto setupText = [&](sf::Text &text, const std::string& string, sf::Vector2f position) -> void {
        text.setString(string);
        text.setCharacterSize(previewPanel.getSize().x * 0.02);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);
    };

    setupText(startText, "New Game", sf::Vector2f(previewPanel.getPosition().x * 0.945f, previewPanel.getPosition().y * 0.875f));
    setupText(continueText, "Continue", sf::Vector2f(previewPanel.getPosition().x * 0.945f, previewPanel.getPosition().y * 1.075f));
    setupText(scoresText, "Best Results", sf::Vector2f(previewPanel.getPosition().x * 0.925f, previewPanel.getPosition().y * 1.27f));
    setupText(instructionText, "Instruction", sf::Vector2f(previewPanel.getPosition().x * 0.925f, previewPanel.getPosition().y * 1.47f));

    setupText(fontText, "Font", sf::Vector2f(previewPanel.getPosition().x * 0.6f, previewPanel.getPosition().y * 0.5f));
    setupText(fontValueText, fontOptions[fontIndex], sf::Vector2f(previewPanel.getPosition().x * 0.6f, previewPanel.getPosition().y * 0.605f));

    setupText(difficultyText, "Difficulty", sf::Vector2f(previewPanel.getPosition().x * 0.925f, previewPanel.getPosition().y * 0.5f));
    setupText(difficultyValueText, difficultyOptions[difficultyIndex], sf::Vector2f(previewPanel.getPosition().x * 0.97f, previewPanel.getPosition().y * 0.605f));

    setupText(topicText, "Topic", sf::Vector2f(previewPanel.getPosition().x * 1.31f, previewPanel.getPosition().y * 0.5f));
    setupText(topicValueText, topicOptions[topicIndex], sf::Vector2f(previewPanel.getPosition().x * 1.3f, previewPanel.getPosition().y * 0.605f));


    auto setupArrowText = [&](sf::Text& arrow, const std::string& string, sf::Vector2f position) -> void {
        arrow.setString(string);
        arrow.setCharacterSize(previewPanel.getSize().x * 0.025);
        arrow.setFillColor(sf::Color::Black);
        arrow.setPosition(position);
    };

    setupArrowText(fontLeftArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.545f, previewPanel.getPosition().y * 0.6f));
    setupArrowText(fontRightArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.7f, previewPanel.getPosition().y * 0.6f));

    setupArrowText(difficultyLeftArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.92f, previewPanel.getPosition().y * 0.6f));
    setupArrowText(difficultyRightArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 1.05f, previewPanel.getPosition().y * 0.6f));

    setupArrowText(topicLeftArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 1.25f, previewPanel.getPosition().y * 0.6f));
    setupArrowText(topicRightArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 1.425f, previewPanel.getPosition().y * 0.6f));

}

auto Preview::processMouseClick(const sf::Vector2f& mousePos) -> void {
    if (fontLeftArrow.getGlobalBounds().contains(mousePos)) {
        fontIndex = (fontIndex - 1 + fontOptions.size()) % fontOptions.size();
        fontValueText.setString(fontOptions[fontIndex]);
        centerText(fontValueText, sf::Vector2f(previewPanel.getPosition().x * 0.63f, previewPanel.getPosition().y * 0.63f));
    }
    if (fontRightArrow.getGlobalBounds().contains(mousePos)) {
        fontIndex = (fontIndex + 1) % fontOptions.size();
        fontValueText.setString(fontOptions[fontIndex]);
        centerText(fontValueText, sf::Vector2f(previewPanel.getPosition().x * 0.63f, previewPanel.getPosition().y * 0.63f));
    }

    if (difficultyLeftArrow.getGlobalBounds().contains(mousePos)) {
        difficultyIndex = (difficultyIndex - 1 + difficultyOptions.size()) % difficultyOptions.size();
        difficultyValueText.setString(difficultyOptions[difficultyIndex]);
        centerText(difficultyValueText, sf::Vector2f(previewPanel.getPosition().x * 0.995f, previewPanel.getPosition().y * 0.63f));
    }
    if (difficultyRightArrow.getGlobalBounds().contains(mousePos)) {
        difficultyIndex = (difficultyIndex + 1) % difficultyOptions.size();
        difficultyValueText.setString(difficultyOptions[difficultyIndex]);
        centerText(difficultyValueText, sf::Vector2f(previewPanel.getPosition().x * 0.995f, previewPanel.getPosition().y * 0.63f));
    }

    if (topicLeftArrow.getGlobalBounds().contains(mousePos)) {
        topicIndex = (topicIndex - 1 + topicOptions.size()) % topicOptions.size();
        topicValueText.setString(topicOptions[topicIndex]);
        centerText(topicValueText, sf::Vector2f(previewPanel.getPosition().x * 1.35f, previewPanel.getPosition().y * 0.63f));
    }
    if (topicRightArrow.getGlobalBounds().contains(mousePos)) {
        topicIndex = (topicIndex + 1) % topicOptions.size();
        topicValueText.setString(topicOptions[topicIndex]);
        centerText(topicValueText, sf::Vector2f(previewPanel.getPosition().x * 1.35f, previewPanel.getPosition().y * 0.63f));
    }
}

auto Preview::centerText(sf::Text& text, sf::Vector2f center) -> void {
    auto bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    text.setPosition(sf::Vector2f(center.x, center.y));
}

auto Preview::render(sf::RenderWindow& window) -> void {
    updateButtons(); // ensure color matches availability

    window.draw(previewPanel);
    window.draw(startButton);
    window.draw(startText);
    window.draw(continueButton);
    window.draw(continueText);
    window.draw(scoresButton);
    window.draw(scoresText);
    window.draw(instructionButton);
    window.draw(instructionText);
    window.draw(fontText);
    window.draw(fontValueText);
    window.draw(fontLeftArrow);
    window.draw(fontRightArrow);
    window.draw(difficultyText);
    window.draw(difficultyValueText);
    window.draw(difficultyLeftArrow);
    window.draw(difficultyRightArrow);
    window.draw(topicText);
    window.draw(topicValueText);
    window.draw(topicLeftArrow);
    window.draw(topicRightArrow);
}

auto Preview::updateButtons() -> void {
    if (GameSave::isSaveAvailable()) {
        continueButton.setFillColor({0, 0, 90});
        continueText.setFillColor(sf::Color::White);
    } else {
        continueButton.setFillColor({100, 100, 100});
        continueText.setFillColor({150, 150, 150});
    }
}

bool Preview::isContinueButtonClicked(const sf::Vector2f& mousePos) const {
    return continueButton.getGlobalBounds().contains(mousePos);
}

auto Preview::isStartButtonClicked(const sf::Vector2f& mousePos) -> bool  {
    return startButton.getGlobalBounds().contains(mousePos);
}

auto Preview::isScoresButtonClicked(const sf::Vector2f& mousePos) -> bool  {
    return scoresButton.getGlobalBounds().contains(mousePos);
}

auto Preview::isInstructionButtonClicked(const sf::Vector2f& mousePos) -> bool  {
    return instructionButton.getGlobalBounds().contains(mousePos);
}

auto Preview::getSelectedFontName() -> std::string {
    return fontOptions[fontIndex];
}
auto Preview::getSelectedDifficulty() -> std::string {
    return difficultyOptions[difficultyIndex];
}
auto Preview::getSelectedTopicName() -> std::string {
    return topicOptions[topicIndex];
}


