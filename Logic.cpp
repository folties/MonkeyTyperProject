#include "Logic.h"

#include <cmath>
#include <iostream>

Logic::Logic() :
    window(sf::VideoMode::getDesktopMode(), "MonkeyTyper", sf::Style::Default, sf::State::Windowed),
    word(pixelFont),
    background(window.getSize()),
    gameEnd(bloxFont, window.getSize()),
    panel(pixelFont, window.getSize()),
    previewScreen(window.getSize()),
    scores(pixelFont, window.getSize()),
    instruction(pixelFont, window.getSize()),
    gameMenu(bloxFont, window.getSize()),
    countdownText(bloxFont, "", 80),
    totalTime(0.f),
    wpm(0.f),
    missed(0.f),
    countdownTime(0.0f)
{
    initResources();
    initUI();
    scores.loadFromFile();
}

auto Logic::initResources() -> void {
    pixelFont = resources.getFont("PixelFont");
    bloxFont  = resources.getFont("BloxFont");
    resources.setIcon(window);
}

auto Logic::initUI() -> void{
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(sf::Vector2f(window.getSize().x * 0.47f, window.getSize().y * 0.45f));
    panel.setWordCounter(0);
    panel.setWPM(0.f);
    panel.setMissedWords(0);
}

auto Logic::run() -> void {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        if (currentStatus == GameStatus::PREVIEW) {
            renderPreview();
        }
        else if (currentStatus == GameStatus::PLAYING) {
            if (!gameStarted) {
                startCountdown(deltaTime);
            } else {
                update(deltaTime);
                renderGame();
            }
        }
    }
}

auto Logic::renderPreview() -> void {
    window.clear(sf::Color::Black);
    previewScreen.render(window);
    scores.render(window);
    instruction.render(window);
    window.display();
}

auto Logic::renderGame() -> void {
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
        gameEnd.render(window);
        resources.getMusic().stop();
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
            if (currentStatus == GameStatus::PLAYING) {
                saveAndExitToPreview();
            }
            window.close();
        }
        else if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f pos(window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y }));
                if (currentStatus == GameStatus::PREVIEW) {
                    handlePreviewMouse(pos);
                }
                else if (currentStatus == GameStatus::PLAYING) {
                    handlePlayingMouse(pos);
                }
            }
        }
        else if (auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
            handleTextInput(textEvent->unicode);
        }
        else if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            shortcut.handleKeyEvent(*keyEvent, typing, word, panel, resources);
        }
    }
}

auto Logic::handleTextInput(uint32_t unicode) -> void {
    if (currentStatus == GameStatus::PLAYING && word.isGameOver()) {
        gameEnd.handleLabelInput(unicode);
    } else if (!shortcut.getMenuGameState()) {
        char typedChar = static_cast<char>(unicode);
        typing.processInput(typedChar);
        panel.setTypedText(typing.getCurrentInput());
        if (shortcut.isTypeSoundEnabled()) {
            resources.typeSoundPlay();
        }
    }
}


auto Logic::handlePreviewMouse(const sf::Vector2f& mousePos) -> void {
    if (scores.isVisible()) {
        scores.handleClick(mousePos);
    }
    else if (previewScreen.isScoresButtonClicked(mousePos)) {
        scores.setCurrentDifficulty(previewScreen.getSelectedDifficulty());
        scores.setVisible(true);
    }
    if (instruction.isVisible()) {
        instruction.handleClick(mousePos);
    }
    else if (previewScreen.isInstructionButtonClicked(mousePos))
        instruction.setVisible(true);

    if (previewScreen.isContinueButtonClicked(mousePos)) {
        onContinue();
    }
    else if (previewScreen.isStartButtonClicked(mousePos)) {
        onStart();
    }
    else {
        previewScreen.processMouseClick(mousePos);
    }
}

auto Logic::onContinue() -> void {
    if (!GameSave::isSaveAvailable()) {
        return;
    }
    auto state = GameSave::loadGame();
    applyLoadedState(state);
    gameStarted = false;
    countdownTime = 3.0f;
    currentStatus = GameStatus::PLAYING;
    resumeGame();
}

auto Logic::onStart() -> void {
    applyFont(previewScreen.getSelectedFontName());
    applyDifficulty(previewScreen.getSelectedDifficulty());
    applyTopic(previewScreen.getSelectedTopicName());
    gameStarted = false;
    countdownTime = 3.0f;
    currentStatus = GameStatus::PLAYING;
}

auto Logic::handlePlayingMouse(const sf::Vector2f& mousePos) -> void {
    if (shortcut.getMenuGameState()) {
        handleMenuActions(mousePos);
    }
    else if (word.isGameOver()) {
        handleGameOverActions(mousePos);
    }
}

auto Logic::handleMenuActions(const sf::Vector2f& mousePos) -> void {
    if (gameMenu.isResumeClicked(mousePos)) {
        resumeGame();
    }
    else if (gameMenu.isLeaveClicked(mousePos)) {
        saveAndExitToPreview();
    }
}

auto Logic::handleGameOverActions(const sf::Vector2f& mousePos) -> void {
    if (gameEnd.isReturnButtonClicked(mousePos)) {
        exitToPreview();
    }
    else if (gameEnd.isSaveButtonClicked(mousePos)) {
        gameEnd.saveResultToFile();
    }
}

auto Logic::resumeGame() -> void {
    shortcut.setMenuGameState(false);
    resources.switchMusic();
}

auto Logic::exitToPreview() -> void {
    resetGame();
    saver.clearSave();
    currentStatus = GameStatus::PREVIEW;
    scores.loadFromFile();
    scores.setCurrentDifficulty(previewScreen.getSelectedDifficulty());
}

auto Logic::applyLoadedState(const GameState& s) -> void {
    applyFont(s.fontName);
    applyDifficulty(s.difficultyLevel);
    applyTopic(s.topic);

    totalTime = s.totalTime;
    panel.setWordCounter(s.wordsClaimed);
    typing.setWordCount(s.wordsClaimed);
    wpm = s.score;

    for (auto& ws : s.words) {
        Words restored(ws.text, pixelFont, 25, sf::Vector2f( ws.posX, ws.posY ));
        restored.speed = ws.speed;
        word.getActiveWords().push_back(restored);
    }
    word.setMissedWords(s.missedWords);
    panel.setMissedWords(s.missedWords);
}

auto Logic::saveAndExitToPreview() -> void {
    GameState s;
    s.topic           = word.getTopic();
    s.fontName        = previewScreen.getSelectedFontName();
    s.difficultyLevel = previewScreen.getSelectedDifficulty();

    s.totalTime       = totalTime;
    s.wordsClaimed    = typing.getWordCount();
    s.score           = wpm;
    s.missedWords     = word.getMissedWords();
    for (auto& w : word.getActiveWords()) {
        WordState ws;
        ws.text  = w.getString();
        ws.posX  = w.getPosition().x;
        ws.posY  = w.getPosition().y;
        ws.speed = w.speed;
        s.words.push_back(ws);
    }

    GameSave::saveGame(s);
    resetGame();
    currentStatus = GameStatus::PREVIEW;
}

auto Logic::applyFont(const std::string& fontName) -> void {
    const sf::Font& f = resources.getFont(fontName + "Font");
    word.setFont(f);
}

auto Logic::applyDifficulty(const std::string& diff) -> void {
    Difficulty level = word.stringToDifficulty(diff);
    word.setDifficulty(level);
    gameEnd.setDifficulty(diff);
    scores.setCurrentDifficulty(diff);
}

auto Logic::applyTopic(const std::string& topic) -> void {
    word.setTopic(topic);
    gameEnd.setTopic(topic);
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
    resources.switchMusic();
    gameEnd.clearLabelAndConfirmation();
}

auto Logic::startCountdown(float deltaTime) -> void {
    countdownTime -= deltaTime;

    if (countdownTime <= 0.f) {
        gameStarted = true;

    } else {
        int displayNumber = static_cast<int>(std::ceil(countdownTime));
        countdownText.setString(std::to_string(displayNumber));

        window.clear(sf::Color(0, 0, 50));
        background.updateStars(deltaTime, window.getSize());
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
        background.updateStars(deltaTime, window.getSize());
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