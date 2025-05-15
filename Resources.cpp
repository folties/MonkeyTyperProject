#include "Resources.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <filesystem>

Resources::Resources(): typeSound(typeBuffer) {
    loadFonts();
    loadMusic();
    loadTypeSound();
    loadIcon();
}

auto Resources::loadIcon() -> void {
    if (!icon.loadFromFile("../materials/images/MonkeyTyperPicture.png")) {
        std::cerr << "Failed to load icon.\n";
    }
}

auto Resources::loadFonts() -> void {
    sf::Font bloxFont;
    if (!bloxFont.openFromFile("../materials/fonts/Blox.ttf")) {
        std::cerr << "Could not load bloxFont\n";
        exit(1);
    }
    fonts["BloxFont"] = std::move(bloxFont); // Save into map

    sf::Font pixelFont;
    if (!pixelFont.openFromFile("../materials/fonts/Pixel.ttf")) {
        std::cerr << "Could not load pixelFont\n";
        exit(1);
    }
    fonts["PixelFont"] = std::move(pixelFont); // Save into map

    sf::Font alphbetaFont;
    if (!alphbetaFont.openFromFile("../materials/fonts/Alphbeta.ttf")) {
        std::cerr << "Could not load alphbetaFont\n";
        exit(1);
    }
    fonts["AlphbetaFont"] = std::move(alphbetaFont); // Save into map

    sf::Font hevillaFont;
    if (!hevillaFont.openFromFile("../materials/fonts/Hevilla.ttf")) {
        std::cerr << "Could not load hefillaFont\n";
        exit(1);
    }
    fonts["HevillaFont"] = std::move(hevillaFont); // Save into map

    sf::Font steveFont;
    if (!steveFont.openFromFile("../materials/fonts/Steve.ttf")) {
        std::cerr << "Could not load steveFont\n";
        exit(1);
    }
    fonts["SteveFont"] = std::move(steveFont); // Save into map DELETE

    sf::Font warworkFont;
    if (!warworkFont.openFromFile("../materials/fonts/Warwork.ttf")) {
        std::cerr << "Could not load warworkFont\n";
        exit(1);
    }
    fonts["WarworkFont"] = std::move(warworkFont); // Save into map DELETE

    sf::Font grosacFont;
    if (!grosacFont.openFromFile("../materials/fonts/Grosac.ttf")) {
        std::cerr << "Could not load grosacFont\n";
        exit(1);
    }
    fonts["GrosacFont"] = std::move(grosacFont); // Save into map
}

auto Resources::loadMusic() -> void {
    if (!backgroundMusic.openFromFile("../materials/music/musicGame.mp3")) { //
        std::cerr << "Could not load background music\n";
        exit(1);
    }
    backgroundMusic.setLooping(true); // so it repeats automatically
}

auto Resources::loadTypeSound() -> void {
    if (!typeBuffer.loadFromFile("../materials/soundEffect/typeSound.ogg")) {
        std::cerr << "Could not load typeSound\n";
        exit(1);
    }
    typeSound.setBuffer(typeBuffer);
}

auto Resources::getFont(const std::string& name) ->  sf::Font&  {
    auto it = fonts.find(name);
    if (it != fonts.end()) {
        return it->second;
    } else {
        std::cerr << "Font not found: " << name << "\n";
        exit(1);
    }
}

auto Resources::getMusic() -> sf::Music&{
    return backgroundMusic;
}

auto Resources::getTypeSound() -> sf::Sound& {
    return typeSound;
}