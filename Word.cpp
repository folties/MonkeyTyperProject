#include "Word.h"
#include <random>
#include <fstream>
#include <iostream>
#include <unordered_set>

Word::Word(const sf::Font& font) {
    this->font = font;
    initWords();
}

//words initialization
auto Word::initWords() -> void {
    wordsList.clear();

    std::string filePath = "../materials/listOfWords/";
    if (selectedTopic == "Animals") {
        filePath += "animalsTopic.txt";
    } else if (selectedTopic == "Technology") {
        filePath += "technologyTopic.txt";
    } else if (selectedTopic == "Nature") {
        filePath += "natureTopic.txt";
    } else {
        filePath += "words.txt"; // fallback
    }

    std::ifstream file(filePath);
    std::string word;
    while (file >> word) {
        wordsList.push_back(word);
    }

    if (wordsList.empty()) {
        std::cerr << "No words loaded from file: " << filePath << "\n";
    } else {
        std::shuffle(wordsList.begin(), wordsList.end(), std::mt19937(std::random_device{}()));
    }
}

auto Word::updateWords(float deltaTime, sf::Vector2u windowSize) -> void {
    // Update step timer globally
    stepTimer += deltaTime;
    bool shouldStep = false;

    if (useStepMovement && stepTimer >= stepInterval) {
        shouldStep = true;
        stepTimer = 0.f;
    }

    float redThreshold = windowSize.x * 0.75f;
    float yellowThreshold = windowSize.x * 0.5f;

    // Move existing words
    for (auto it = objectsWords.begin(); it != objectsWords.end();) {
        sf::Vector2f position = it->getPosition();

        if (useStepMovement) {
            if (shouldStep) {
                position.x += windowSize.x * 0.01f;  // step = 1% of screen width
            }
        } else {
            position.x += it->speed * deltaTime;  // smooth movement
        }

        // Color priority logic here
        if (position.x > redThreshold) {
            it->setFillColor(sf::Color::Red);
        } else if (position.x > yellowThreshold) {
            it->setFillColor(sf::Color::Yellow);
        } else {
            it->setFillColor(sf::Color::Cyan);
        }

        if (position.x > static_cast<float>(windowSize.x)) {
            missedWords++;
            it = objectsWords.erase(it);
        } else {
            it->setPosition(position);
            ++it;
        }
    }


    // Time-controlled spawning
    wordSpawnTimer += deltaTime;
    if (wordSpawnTimer >= wordSpawnInterval && nextWordIndex < wordsList.size()) {
        wordSpawnTimer = 0.f;

        const float spacingY = windowSize.y * 0.04f;      // each line ~4% of height
        const float minDistance = windowSize.x * 0.07f;   // min dist between words in same row

        float panelHeight = windowSize.y * 0.05f; // panel is 5% of the screen
        int maxSlots = static_cast<int>((windowSize.y - panelHeight) / spacingY);
        std::vector<int> possibleSlots;

        for (int slot = 0; slot < maxSlots; ++slot) {
            float y = slot * spacingY;
            bool isFarEnough = true;

            for (const auto& word : objectsWords) {
                if (word.getPosition().y == y && word.getPosition().x < minDistance) {
                    isFarEnough = false;
                    break;
                }
            }

            if (isFarEnough) {
                possibleSlots.push_back(slot);
            }
        }

        if (!possibleSlots.empty()) {
            std::mt19937 random(static_cast<unsigned>(time(nullptr)));
            std::uniform_int_distribution<int> dist(0, possibleSlots.size() - 1);
            int ySlot = possibleSlots[dist(random)];

            float y = ySlot * spacingY;

            Words newWord(wordsList[nextWordIndex], font);
            newWord.setPosition(sf::Vector2f(-100, y)); // Start slightly offscreen
            newWord.setCharacterSize(static_cast<unsigned>(windowSize.y * 0.025f)); // 3% of height
            newWord.speed = windowSize.x * 0.05f; // speed is 5% of width per second
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
    for (const auto& word : objectsWords) {
        window.draw(word);
    }
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
auto Word::setFont(const sf::Font& newFont) -> void {
    font = newFont;
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
        wordSpawnInterval = 1.5f;
    } else if (difficulty == Difficulty::MEDIUM) {
        wordSpawnInterval = 1.0f;
    } else if (difficulty == Difficulty::HARD) {
        wordSpawnInterval = 0.7f;
    } else if (difficulty == Difficulty::INSANE) {
        wordSpawnInterval = 0.5f;
    }
}

auto Word::setTopic(const std::string& topic) -> void {
    this->selectedTopic = topic;
    initWords();  // Re-load words from the new topic
}

auto Word::getTopic() -> std::string {
    return selectedTopic;
}

auto Word::reset() -> void {
    objectsWords.clear();
    nextWordIndex = 0;
    missedWords = 0;
    wordSpawnTimer = 0.f;
    usedYSteps.clear();
    stepTimer = 0.f;
    initWords();
}
