#ifndef TYPING_H
#define TYPING_H
#include "Word.h"

#pragma once

class Typing {
public:
    auto processInput(char typedChar) -> void;
    auto trySubmit(Word& word) -> void;
    auto getCurrentInput() -> std::string;
    auto getWordCount() -> int;
    auto reset() -> void;

private:
    std::string currentInput;
    int wordCounter = 0;
};



#endif //TYPING_H
