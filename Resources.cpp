//
// Created by MSI on 14.05.2025.
//

#include "Resources.h"

#include <iostream>

Resources::Resources() : sound(soundBuffer) {
    std::cout << "Starting resource loading..." << std::endl;
    loadFont();
    loadMusic();
    loadSound();
    loadIcon();
    std::cout << "Resource loading complete" << std::endl;
}


auto Resources::loadIcon() -> void {
    if (!icon.loadFromFile("../materials/images/MonkeyTyperPicture.png")) {
        std::cerr << "ERROR: Failed to load icon from file: ../materials/images/MonkeyTyperPicture.png" << std::endl;
    }
}

auto Resources::loadFont() -> void {
    std::cout << "Starting font loading..." << std::endl;

    sf::Font bloxFont;
    if (!bloxFont.openFromFile("../materials/fonts/Blox.ttf")) {
        std::cerr << "ERROR: Failed to load bloxFont from: ../materials/fonts/Blox.ttf" << std::endl;
    } else {
        std::cout << "Successfully loaded Blox.ttf" << std::endl;
    }
    fonts["BloxFont"] = std::move(bloxFont);

    sf::Font pixelFont;
    if (!pixelFont.openFromFile("../materials/fonts/Pixel.ttf")) {
        std::cerr << "ERROR: Failed to load pixelFont from: ../materials/fonts/Pixel.ttf" << std::endl;
    }
    fonts["PixelFont"] = std::move(pixelFont);

    sf::Font alphbetaFont;
    if (!alphbetaFont.openFromFile("../materials/fonts/Alphbeta.ttf")) {
        std::cerr << "ERROR: Failed to load alphbetaFont from: ../materials/fonts/Alphbeta.ttf" << std::endl;
    }
    fonts["AlphbetaFont"] = std::move(alphbetaFont);

    sf::Font hevillaFont;
    if (!hevillaFont.openFromFile("../materials/fonts/Hevilla.ttf")) {
        std::cerr << "ERROR: Failed to load hefillaFont from: ../materials/fonts/Hevilla.ttf" << std::endl;
    }
    fonts["HevillaFont"] = std::move(hevillaFont);

    sf::Font steveFont;
    if (!steveFont.openFromFile("../materials/fonts/Steve.ttf")) {
        std::cerr << "ERROR: Failed to load steveFont from: ../materials/fonts/Steve.ttf" << std::endl;
    }
    fonts["SteveFont"] = std::move(steveFont);

    sf::Font warworkFont;
    if (!warworkFont.openFromFile("../materials/fonts/Warwork.ttf")) {
        std::cerr << "ERROR: Failed to load warworkFont from: ../materials/fonts/Warwork.ttf" << std::endl;
    }
    fonts["WarworkFont"] = std::move(warworkFont);

    sf::Font grosacFont;
    if (!grosacFont.openFromFile("../materials/fonts/Grosac.ttf")) {
        std::cerr << "ERROR: Failed to load grosacFont from: ../materials/fonts/Grosac.ttf" << std::endl;
    }
    fonts["GrosacFont"] = std::move(grosacFont);

    std::cout << "Font loading complete" << std::endl;
}

auto Resources::loadMusic() -> void {
    if (!music.openFromFile("../materials/music/musicGame.mp3")) {
        std::cerr << "ERROR: Failed to load music from: ../materials/music/musicGame.mp3" << std::endl;
    }
    music.setLooping(true);
}

auto Resources::loadSound() -> void {
    if (!soundBuffer.loadFromFile("../materials/soundEffect/typeSoundEffect.ogg")) {
        std::cerr << "ERROR: Failed to load typeSound from: ../materials/soundEffect/typeSoundEffect.ogg" << std::endl;
    }
    sound.setBuffer(soundBuffer);
}

auto Resources::getFont(const std::string& font) -> sf::Font& {
    std::cout << "Attempting to get font: " << font << std::endl;
    auto iterator = fonts.find(font);
    if (iterator != fonts.end()) {
        std::cout << "Successfully found font: " << font << std::endl;
        return iterator->second;
    } else {
        std::cerr << "ERROR: Failed to find font: " << font << std::endl;
        throw std::runtime_error("Failed to find font");
    }
}
