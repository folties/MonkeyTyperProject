#include "Logic.h"

#include <cmath>
#include <iostream>


Logic::Logic()
    : window(sf::VideoMode::getDesktopMode(), "MonkeyTyper", sf::Style::Close, sf::State::Windowed),
      background(window.getSize()),
      word(pixelFont),
      gameEnd(bloxFont),
      panel(pixelFont, window.getSize()),
      countdownText(bloxFont, "", 80),
      totalTime(0.f),
      wpm(0.f),
      missed(0.f),
      gameStarted(false),
      countdownTime(3.0f),
      previewScreen(window.getSize()),
      scores(pixelFont, window.getSize().x, window.getSize().y),
      instruction(pixelFont, window.getSize()),
      gameMenu(bloxFont, window.getSize().x, window.getSize().y)
{
    window.setMouseCursorGrabbed(false);

    pixelFont = resources.getFont("PixelFont");
    bloxFont = resources.getFont("BloxFont");
    window.setIcon(resources.icon);
    window.setMouseCursorVisible(true);

    // --- UI Setup ---
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(sf::Vector2f(window.getSize().x * 0.47f, window.getSize().y * 0.45f));
    panel.setWordCounter(typing.getWordCount());
    panel.setWPM(wpm);
    panel.setMissedWords(word.getMissedWords());
    // --- Load Scores ---
    scores.loadFromFile();
}

// ===== Main Loop =====
auto Logic::run() -> void {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();

        if (currentState == GameState::PREVIEW) {
            renderPreview();
        }
        else if (currentState == GameState::PLAYING) {
            if (!gameStarted) {
                startCountdown(deltaTime);
            } else {
                update(deltaTime);
                render();
            }
        }
    }
}

// ===== Rendering =====
auto Logic::renderPreview() -> void {
    window.clear(sf::Color::Black);
    previewScreen.render(window);
    scores.render(window);
    instruction.render(window);
    window.display();
}

auto Logic::render() -> void {
    window.clear(sf::Color(0, 0, 50));

    if (!word.isGameOver()) {
        background.drawStars(window);
        word.drawWord(window);
    } else {
        window.clear(sf::Color::Black);
        gameEnd.setWPM(wpm);
        gameEnd.setTime(totalTime);
        gameEnd.setMissedWords(missed);
        gameEnd.setTypedText(typing.getCurrentInput());
        gameEnd.show(window);
        resources.backgroundMusic.stop();
    }

    if (!word.isGameOver()) {
        panel.draw(window);
    }

    if (shortcut.getMenuGameState()) {
        gameMenu.render(window);
    }

    window.display();
}

auto Logic::processEvents() -> void {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos(window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y }));

                if (currentState == GameState::PREVIEW) {
                    if (scores.isVisible()) {
                        scores.handleClick(mousePos);
                    } else if (previewScreen.isScoresButtonClicked(mousePos)) {
                        scores.setCurrentDifficulty(previewScreen.getSelectedDifficulty());
                        scores.setVisible(true);
                    }
                        if (instruction.isVisible()) {
                            instruction.handleClick(mousePos);
                        } else if (previewScreen.isInstructionButtonClicked(mousePos)) {
                            instruction.setVisible(true);
                        }
                        if (previewScreen.isStartButtonClicked(mousePos)) {
                            // 1. Get selected font name from PreviewScreen
                            std::string selectedFont = previewScreen.getSelectedFontName();

                            // 2. Update font everywhere (Word, Panel, etc.)
                            const sf::Font& newFont = resources.getFont(selectedFont + "Font"); // <-- careful with the name

                            word.setFont(newFont);

                            std::string selectedDifficulty = previewScreen.getSelectedDifficulty();
                            word.setDifficulty(word.stringToDifficulty(selectedDifficulty));
                            gameEnd.setDifficulty(selectedDifficulty);
                            scores.setCurrentDifficulty(selectedDifficulty);

                            std::string selectedTopic = previewScreen.getSelectedTopicName();
                            word.setTopic(selectedTopic); // <- Add this function

                            currentState = GameState::PLAYING;
                        } else {
                            previewScreen.processMouseClick(mousePos);
                        }
                    } else if (currentState == GameState::PLAYING) {
                        if (shortcut.getMenuGameState()) {
                            if (gameMenu.isResumeClicked(mousePos)) {
                                shortcut.setMenuGameState(false);  // Hide the menu
                                resources.backgroundMusic.play();  // Resume music
                            }
                            if (gameMenu.isLeaveClicked(mousePos)) {
                                shortcut.setMenuGameState(false);
                                currentState = GameState::PREVIEW;
                                resetGame();

                            }
                        }


                        if (word.isGameOver()) {
                            if (gameEnd.isReturnButtonClicked(mousePos)) {
                                currentState = GameState::PREVIEW;
                                resetGame();
                                scores.loadFromFile();
                                scores.setCurrentDifficulty(previewScreen.getSelectedDifficulty());
                            } else if (gameEnd.isSaveButtonClicked(mousePos)) {
                                gameEnd.setTopic(word.getTopic());  // Set the topic before saving
                                bool success = gameEnd.saveResultToFile();
                                gameEnd.showConfirmation(success);
                            }
                        }
                    }
                }
            }

            if (auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                if (currentState == GameState::PLAYING && word.isGameOver()) {
                    gameEnd.handleLabelInput(textEvent->unicode);
                } else if (!shortcut.getMenuGameState()) {
                    char typedChar = static_cast<char>(textEvent->unicode);
                    typing.processInput(typedChar);
                    panel.setTypedText(typing.getCurrentInput());

                    if (shortcut.isTypeSoundEnabled()) {
                        resources.typeSound.stop(); // (optional, to prevent overlap)
                        resources.typeSound.play();
                    }
                }
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                shortcut.handleKeyEvent(*keyEvent, typing, word, panel, resources, gameMenu);
            }
        }
    }


auto Logic::resetGame() -> void {
    totalTime = 0.f;
    wpm = 0.f;
    missed = 0.f;
    gameStarted = false;
    countdownTime = 3.0f;
    word.reset();
    typing.reset();
    panel.reset();
    resources.backgroundMusic.stop();
    gameEnd.clearLabelAndConfirmation();
}

auto Logic::startCountdown(float deltaTime) -> void {
    countdownTime -= deltaTime;

    if (countdownTime <= 0.f) {
        gameStarted = true;

        resources.backgroundMusic.play();
    } else {
        int displayNumber = static_cast<int>(std::ceil(countdownTime));
        countdownText.setString(std::to_string(displayNumber));

        window.clear(sf::Color(0, 0, 50));
        background.updateStars(deltaTime);
        background.drawStars(window);
        window.draw(countdownText);
        window.display();
    }
}

auto Logic::update(float deltaTime) -> void {
    if (!shortcut.getMenuGameState() && !word.isGameOver()) {
        totalTime += deltaTime;

        if (totalTime > 0) {
            wpm = (typing.getWordCount() / totalTime) * 60.f;
            panel.setWPM(wpm);
        }

        panel.setTimer(totalTime);
        panel.setTraffic(countVisibleWords(), word.getTotalWords());
        word.updateWords(deltaTime, window.getSize());
        background.updateStars(deltaTime);
        panel.setMissedWords(word.getMissedWords());
        missed = word.getMissedWords();
    }
}

auto Logic::countVisibleWords() -> int {
    int visibleWords = 0;
    for (const auto& w : word.getActiveWords()) {
        if (w.getPosition().x >= 20) {
            ++visibleWords;
        }
    }
    return visibleWords;
}

//TODO:add stats
//TODO:add settings
//TODO:different background and mode(dark, white)
//TODO:music for 2d games that gives beat each second
//TODO:add sound effects
//TODO:add permissions
//TODO:add restrictions to prevent from writing when paused and writing a lot
//TODO:what is going on in gameEnd cpp
//TODO:levels
//TODO:fonts
//TODO:music
//TODO:shortcuts key : paused, words movement
//TODO:different words topic
//TODO::Game history
//TODO:use fmt::format instead ostringstream

//TODO:add game over when missedWords=10
//TODO:add saving point

