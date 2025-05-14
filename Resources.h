#ifndef RESOURCES_H
#define RESOURCES_H

#pragma once

#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Resources {
public:
    Resources();

    auto getFont(const std::string& font) -> sf::Font&;

private:
    auto loadFont() -> void;
    auto loadMusic() -> void;
    auto loadSound() -> void;
    auto loadIcon() -> void;

    std::map<std::string, sf::Font> fonts;
    sf::Image icon;
    sf::Music music;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
};



#endif //RESOURCES_H
