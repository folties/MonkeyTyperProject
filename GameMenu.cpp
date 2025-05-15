#include "GameMenu.h"

GameMenu::GameMenu(const sf::Font& font, float width, float height)
    : width(width), height(height),
      titleText(font, "Pause Menu", 100),
      resumeText(font, "resume", 35),
      leaveText(font, "quit", 35)
{
    // Panel
    panel.setSize(sf::Vector2f(width, height));
    panel.setFillColor(sf::Color(30, 30, 40));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(10.f);
    panel.setOrigin(panel.getSize() / 2.f);
    panel.setPosition(sf::Vector2f(width / 2.f, height / 2.f));

    // Title
    titleText.setFillColor(sf::Color(200, 200, 200));
    titleText.setPosition(sf::Vector2f(panel.getPosition().x - 250.f, panel.getPosition().y - 200.f));

    // Resume Button
    resumeButton.setSize(sf::Vector2f(300.f, 60.f));
    resumeButton.setFillColor(sf::Color(90, 120, 180));
    resumeButton.setOutlineColor(sf::Color::White);
    resumeButton.setOutlineThickness(3.f);
    resumeButton.setOrigin(resumeButton.getSize() / 2.f);
    resumeButton.setPosition(sf::Vector2f(panel.getPosition().x, panel.getPosition().y + 30));

    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(sf::Vector2f(resumeButton.getPosition().x - 60, resumeButton.getPosition().y - 20));

    // Leave Button
    leaveButton.setSize(sf::Vector2f(300.f, 60.f));
    leaveButton.setFillColor(sf::Color(90, 60, 90));
    leaveButton.setOutlineColor(sf::Color::White);
    leaveButton.setOutlineThickness(3.f);
    leaveButton.setOrigin(leaveButton.getSize() / 2.f);
    leaveButton.setPosition(sf::Vector2f(panel.getPosition().x, panel.getPosition().y + 120));

    leaveText.setFillColor(sf::Color::White);
    leaveText.setPosition(sf::Vector2f(leaveButton.getPosition().x - 40, leaveButton.getPosition().y - 20));
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