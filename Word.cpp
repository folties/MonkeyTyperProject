#include "Word.h"
#include <random>
#include <fstream>
#include <iostream>

Word::Word()
{
    initWords();
}

auto Word::initWords() -> void {
    wordsList.clear();
    std::string path = "../materials/listOfWords/" + selectedTopic + ".txt";
    std::ifstream file(path);
    std::string w;
    while (file >> w) {
        wordsList.push_back(w);
    }
    if (wordsList.empty()) {
        std::cerr << "Failed to load words from " << path << "\n";
    }
    std::shuffle(wordsList.begin(), wordsList.end(), std::mt19937{std::random_device{}()});
}


auto Word::updateWords(float deltaTime, sf::Vector2u windowSize) -> void {
    stepTimer += deltaTime;
    bool step = useStepMovement && (stepTimer >= stepInterval);
    if (step) {
        stepTimer = 0;
    }
    float redThreshold = windowSize.x * 0.75f;
    float yellowThreshold = windowSize.x * 0.5f;

    for (auto it = objectsWords.begin(); it != objectsWords.end();) {
        auto& word = *it;
        auto position = word.getPosition();

        if (step) {
            position.x = position.x + (windowSize.x * 0.005f);
        } else {
            position.x = position.x + (speed * deltaTime);
        }

        if (position.x > redThreshold) {
            word.setFillColor(sf::Color::Red);
        } else if (position.x > yellowThreshold) {
            word.setFillColor(sf::Color::Yellow);
        } else {
            word.setFillColor(sf::Color::Cyan);
        }

        if (position.x > windowSize.x) {
            missedWords++;
            it = objectsWords.erase(it);
        } else {
            word.setPosition(position);
            ++it;
        }
    }

    wordSpawnTimer += deltaTime;
    if (wordSpawnTimer >= wordSpawnInterval && nextWordIndex < wordsList.size()) {
        wordSpawnTimer = 0.f;

        float spacingY = windowSize.y * 0.04f;
        float minDistance = windowSize.x * 0.07f;
        float panelHeight = windowSize.y * 0.05f;

        int maxSlots = static_cast<int>((windowSize.y - panelHeight) / spacingY);
        std::vector<int> possibleSlots;

        for (int slot = 0; slot < maxSlots; ++slot) {
            float y = slot * spacingY;
            bool isFarEnough = true;

            for (auto& word : objectsWords) {
                if (word.getPosition().y == y && word.getPosition().x < minDistance) {
                    isFarEnough = false;
                }
            }

            if (isFarEnough) {
                possibleSlots.push_back(slot);
            }
        }

        if (!possibleSlots.empty()) {
            std::mt19937 random(static_cast<unsigned>(time(0)));
            std::uniform_int_distribution<int> dist(0, possibleSlots.size() - 1);
            int ySlot = possibleSlots[dist(random)];

            float y = ySlot * spacingY;

            Words newWord(wordsList[nextWordIndex], font, windowSize.y * 0.025f, sf::Vector2f(-100, y));
            objectsWords.push_back(newWord);

            nextWordIndex++;
        }
    }
}

auto Word::toggleMovementMode() -> void {
        useStepMovement = !useStepMovement;
    }

auto Word::isGameOver() -> bool {
        return (nextWordIndex >= wordsList.size() && objectsWords.empty()) || missedWords >= 10;
    }

auto Word::drawWord(sf::RenderWindow& window) -> void {
    for (auto& word : objectsWords) {
        window.draw(word);
    }
}

auto Word::countVisibleWords() -> int {
    int visibleWords = 0;
    for (auto& word : objectsWords) {
        if (word.getPosition().x >= 20) {
            ++visibleWords;
        }
    }
    return visibleWords;
}

auto Word::stringToDifficulty(const std::string& str) -> Difficulty {
    if (str == "Easy") return Difficulty::EASY;
    if (str == "Medium") return Difficulty::MEDIUM;
    if (str == "Hard") return Difficulty::HARD;
    if (str == "Insane") return Difficulty::INSANE;
    return Difficulty::EASY;
}

auto Word::setDifficulty(Difficulty difficulty) -> void {
    selectedDifficulty = difficulty;
    if (difficulty == Difficulty::EASY) {
        wordSpawnInterval = 2.0f;
    } else if (difficulty == Difficulty::MEDIUM) {
        wordSpawnInterval = 1.5f;
    } else if (difficulty == Difficulty::HARD) {
        wordSpawnInterval = 1.0f;
    } else if (difficulty == Difficulty::INSANE) {
        wordSpawnInterval = 0.5f;
    }
}

auto Word::setMissedWords(int missed) -> void {
    missedWords = missed;
}

auto Word::setFont(const sf::Font& newFont) -> void {
    font = newFont;
}

auto Word::setTopic(const std::string& topic) -> void {
    this->selectedTopic = topic;
    initWords();
}

auto Word::getNextWordIndex() -> size_t {
    return nextWordIndex;
}

auto Word::setNextWordIndex(size_t index) -> void {
    nextWordIndex = index;
}

auto Word::getActiveWords() -> std::vector<Words>& {
    return objectsWords;
}

auto Word::getTotalWords() -> int {
    return static_cast<int>(wordsList.size());
}

auto Word::getMissedWords() -> int {
    return missedWords;
}

auto Word::getTopic() -> std::string {
    return selectedTopic;
}

auto Word::getFont() -> sf::Font& {
    return font;
}

auto Word::reset() -> void {
    objectsWords.clear();
    nextWordIndex = 0;
    missedWords = 0;
    wordSpawnTimer = 0.f;
    stepTimer = 0.f;
    initWords();
}
