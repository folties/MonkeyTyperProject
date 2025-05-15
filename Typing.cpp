#include "Typing.h"

auto Typing::processInput(char typedChar) -> void {
    // Support backspace
    if (typedChar == 8 && !currentInput.empty()) {
        currentInput.pop_back();
    } else if (typedChar >= 32 && typedChar <= 126) {
        // printable ASCII
        if (currentInput.size() < 15) {
            currentInput += typedChar;
        }
    }
}
auto Typing::trySubmit(Word& word) -> void {
    auto& activeWords = word.getActiveWords(); // make sure you expose this in Word

    for (auto it = activeWords.begin(); it != activeWords.end(); ++it) {
        if (it->getString() == currentInput) {
            activeWords.erase(it);
            wordCounter++;
            break;
        }
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