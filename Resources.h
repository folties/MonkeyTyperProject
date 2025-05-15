#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

#pragma once

class Resources {
public:
    Resources();

    auto loadIcon() -> void;

    auto getFont(const std::string& name) -> sf::Font&;
    auto getMusic() -> sf::Music&;
    auto getTypeSound() -> sf::Sound&;

    sf::Music backgroundMusic;

    sf::SoundBuffer typeBuffer;
    sf::Sound typeSound;

    sf::Image icon;
private:

    auto loadFonts() -> void;
    auto loadMusic() -> void;
    auto loadTypeSound() -> void;

    std::map<std::string, sf::Font> fonts;
};

#endif // RESOURCES_H