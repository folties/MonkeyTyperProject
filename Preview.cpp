#include "Preview.h"

Preview::Preview(const sf::Vector2u& windowSize) :
    previewFont(resource.getFont("BloxFont")),
    startText(previewFont),
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
    previewPanel.setSize(sf::Vector2f(windowSize.x * 0.7f, windowSize.y * 0.7f));
    previewPanel.setFillColor(sf::Color(180, 180, 180));
    previewPanel.setOutlineColor(sf::Color(0,0,100));
    previewPanel.setOutlineThickness(5.f);
    previewPanel.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    startButton.setSize(sf::Vector2f(280.f, 90.f));
    startButton.setFillColor(sf::Color(0, 0, 90));
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(3.f);
    startButton.setOrigin(startButton.getSize() / 2.f);
    startButton.setPosition(sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

    // Scores button setup
    scoresButton.setSize(sf::Vector2f(200.f, 50.f));
    scoresButton.setFillColor(sf::Color(0, 0, 60));
    scoresButton.setOutlineColor(sf::Color::White);
    scoresButton.setOutlineThickness(3.f);
    scoresButton.setOrigin(scoresButton.getSize() / 2.f);
    scoresButton.setPosition(sf::Vector2f(previewPanel.getPosition().x * 0.3f, previewPanel.getPosition().y * 0.3f));

    instructionButton.setSize(sf::Vector2f(200.f, 50.f));
    instructionButton.setFillColor(sf::Color(0, 0, 60));
    instructionButton.setOutlineColor(sf::Color::White);
    instructionButton.setOutlineThickness(3.f);
    instructionButton.setOrigin(scoresButton.getSize() / 2.f);
    instructionButton.setPosition(sf::Vector2f(previewPanel.getPosition().x * 0.4f, previewPanel.getPosition().y * 0.4f));

    auto setupText = [&](sf::Text &text, const std::string& string, sf::Vector2f position) -> void {
        text.setString(string);
        text.setCharacterSize(previewPanel.getSize().x * 0.3);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);
    };

    setupText(startText, "Start New Game", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupText(scoresText, "Best Results", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupText(instructionText, "Instruction", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

    setupText(fontText, "Font", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupText(fontValueText, fontOptions[fontIndex], sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

    setupText(difficultyText, "Difficulty", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupText(difficultyValueText, difficultyOptions[difficultyIndex], sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

    setupText(topicText, "Topic", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupText(topicValueText, topicOptions[topicIndex], sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));


    auto setupArrowText = [&](sf::Text& arrow, const std::string& string, sf::Vector2f position) -> void {
        arrow.setString(string);
        arrow.setCharacterSize(previewPanel.getSize().x * 0.2);
        arrow.setFillColor(sf::Color::Black);
        arrow.setPosition(position);
    };

    setupArrowText(fontLeftArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupArrowText(fontRightArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

    setupArrowText(difficultyLeftArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupArrowText(difficultyRightArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

    setupArrowText(topicLeftArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));
    setupArrowText(topicRightArrow, "x", sf::Vector2f(previewPanel.getPosition().x * 0.5f, previewPanel.getPosition().y * 0.5f));

}

auto Preview::render(sf::RenderWindow& window) -> void {
    window.draw(previewPanel);
    window.draw(startButton);
    window.draw(startText);
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

