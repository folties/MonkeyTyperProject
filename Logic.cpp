#include "Logic.h"
#include <cmath>

Logic::Logic() :
    window(sf::VideoMode::getDesktopMode(), "MonkeyTyper", sf::Style::Default, sf::State::Windowed),
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
    resources.getMusic().play();
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
        if (currentStatus == GameStatus::PLAYING) {
            if (!gameStarted) {
                startCountdown(deltaTime);
            } else {
                update(deltaTime);
                renderGame();
            }
        }
        if (currentStatus == GameStatus::GAME_OVER) {
            renderGameOver();
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
    background.drawStars(window);
    word.drawWord(window);
    panel.drawPanel(window);

    if (shortcut.getMenuGameState()) {
        gameMenu.render(window);
    }
    window.display();
}

auto Logic::renderGameOver() -> void {
    window.clear(sf::Color::Black);
    gameEnd.setWPM(wpm);
    gameEnd.setTime(totalTime);
    gameEnd.setMissedWords(missed);
    gameEnd.setTypedText(typing.getCurrentInput());
    gameEnd.render(window);
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
                else if (currentStatus == GameStatus::GAME_OVER) {
                    handleGameOverActions(pos);
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
    if (currentStatus == GameStatus::PLAYING && gameStarted && !shortcut.getMenuGameState() ) {
        char typedChar = static_cast<char>(unicode);
        typing.processInput(typedChar);
        panel.setTypedText(typing.getCurrentInput());
        if (shortcut.isTypeSoundEnabled()) {
            resources.typeSoundPlay();
        }
    }
    if (currentStatus == GameStatus::GAME_OVER) {
        gameEnd.handleLabelInput(unicode);
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
}

auto Logic::handleMenuActions(const sf::Vector2f& mousePos) -> void {
    if (gameMenu.isResumeClicked(mousePos)) {
        resumeGame();
    }
    else if (gameMenu.isLeaveClicked(mousePos)) {
        saveAndExitToPreview();
        shortcut.setMenuGameState(false);
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
}

auto Logic::exitToPreview() -> void {
    resetGame();
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
        Words restored(ws.text, word.getFont(), 25, sf::Vector2f( ws.posX, ws.posY ));
        restored.speed = ws.speed;
        word.getActiveWords().push_back(restored);
    }
    word.setMissedWords(s.missedWords);
    panel.setMissedWords(s.missedWords);
    word.setNextWordIndex(s.nextWordIndex);
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
    s.nextWordIndex = word.getNextWordIndex();

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
    gameEnd.clearLabelAndConfirmation();
}

auto Logic::startCountdown(float deltaTime) -> void {
    countdownTime -= deltaTime;

    if (countdownTime <= 0.f) {
        gameStarted = true;

    } else {
        countdownText.setString(std::to_string(static_cast<int>(std::ceil(countdownTime))));

        window.clear(sf::Color(0, 0, 50));
        background.updateStars(deltaTime, window.getSize());
        background.drawStars(window);
        window.draw(countdownText);
        window.display();
    }
}

auto Logic::update(float deltaTime) -> void {
    if (word.isGameOver()){
        saver.clearSave();
        currentStatus = GameStatus::GAME_OVER;
        return;
    }

    if (!shortcut.getMenuGameState()) {
        totalTime += deltaTime;

        if (totalTime > 0) {
            wpm = (typing.getWordCount() / totalTime) * 60.f;
            panel.setWPM(wpm);
        }

        panel.setTimer(totalTime);
        panel.setTraffic(word.countVisibleWords(), word.getTotalWords());
        word.updateWords(deltaTime, window.getSize());
        background.updateStars(deltaTime, window.getSize());
        panel.setMissedWords(word.getMissedWords());
        missed = word.getMissedWords();
    }
}

