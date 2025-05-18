#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

#pragma once

class Resources {
public:
    Resources();

    auto getFont(const std::string& name) -> sf::Font&;
    auto getMusic() -> sf::Music&;
    auto getTypeSound() -> sf::Sound&;

    auto switchMusic() -> void;
    auto typeSoundPlay() -> void;
    auto setIcon(sf::RenderWindow& window) -> void;

private:
    auto loadIcon() -> void;
    auto loadFonts() -> void;
    auto loadMusic() -> void;
    auto loadTypeSound() -> void;

    sf::Image icon;
    sf::SoundBuffer typeBuffer;
    sf::Sound typeSound;
    sf::Music backgroundMusic;

    std::map<std::string, sf::Font> fonts;
};

#endif // RESOURCES_H