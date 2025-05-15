#include "GameMenu.h"

GameMenu::GameMenu(const sf::Font& font, const sf::Vector2u& windowSize) :
      titleText(font, "Pause Menu"),
      resumeText(font, "resume"),
      leaveText(font, "quit")
{
    // Panel
    panel.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    panel.setFillColor(sf::Color(30, 30, 40));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(10.f);
    panel.setOrigin(panel.getSize() / 2.f);
    panel.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    // Title
    titleText.setFillColor(sf::Color(200, 200, 200));
    titleText.setPosition(sf::Vector2f(panel.getPosition().x * 0.73f, panel.getPosition().y * 0.5f));
    titleText.setCharacterSize(windowSize.y * 0.1f);

    // Resume Button
    resumeButton.setSize(sf::Vector2f(windowSize.x * 0.17f, windowSize.y * 0.05f));
    resumeButton.setFillColor(sf::Color(90, 120, 180));
    resumeButton.setOutlineColor(sf::Color::White);
    resumeButton.setOutlineThickness(3.f);
    resumeButton.setOrigin(resumeButton.getSize() / 2.f);
    resumeButton.setPosition(sf::Vector2f(panel.getPosition().x, panel.getPosition().y * 0.9f));

    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(sf::Vector2f(resumeButton.getPosition().x * 0.955f , resumeButton.getPosition().y * 0.965f ));

    // Leave Button
    leaveButton.setSize(sf::Vector2f(windowSize.x * 0.17f, windowSize.y * 0.05f));
    leaveButton.setFillColor(sf::Color(90, 60, 90));
    leaveButton.setOutlineColor(sf::Color::White);
    leaveButton.setOutlineThickness(3.f);
    leaveButton.setOrigin(leaveButton.getSize() / 2.f);
    leaveButton.setPosition(sf::Vector2f(panel.getPosition().x, panel.getPosition().y * 1.1f));

    leaveText.setFillColor(sf::Color::White);
    leaveText.setPosition(sf::Vector2f(leaveButton.getPosition().x * 0.97f, leaveButton.getPosition().y * 0.975f ));
}

auto GameMenu::render(sf::RenderWindow& window) -> void {
    window.draw(panel);
    window.draw(titleText);
    window.draw(resumeButton);
    window.draw(resumeText);
    window.draw(leaveButton);
    window.draw(leaveText);
}

auto GameMenu::isResumeClicked(const sf::Vector2f& mousePos) -> bool {
    return resumeButton.getGlobalBounds().contains(mousePos);
}

auto GameMenu::isLeaveClicked(const sf::Vector2f& mousePos) -> bool {
    return leaveButton.getGlobalBounds().contains(mousePos);
} 