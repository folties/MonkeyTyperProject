#include "Typing.h"

auto Typing::processInput(char typedChar) -> void {
    if (typedChar == 8 && !currentInput.empty()) {
        currentInput.pop_back();
    } else if (typedChar >= 32 && typedChar <= 126) {
        if (currentInput.size() < 15) {
            currentInput += typedChar;
        }
    }
}
auto Typing::trySubmit(Word& word) -> void {
    auto& activeWords = word.getActiveWords();

    auto it = std::find_if(activeWords.begin(), activeWords.end(), [&](const auto& word) {
        return word.getString() == currentInput;
    });

    if (it != activeWords.end()) {
        activeWords.erase(it);
        wordCounter++;
    }
    currentInput.clear();
}

auto Typing::getCurrentInput() -> std::string {
    return currentInput;
}

auto Typing::getWordCount() -> int{
    return wordCounter;
}

auto Typing::reset() -> void {
    currentInput.clear();
    wordCounter = 0;
}