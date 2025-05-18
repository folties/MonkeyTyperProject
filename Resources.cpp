#include "Resources.h"
#include <iostream>

Resources::Resources(): typeSound(typeBuffer) {
    loadFonts();
    loadMusic();
    loadTypeSound();
    loadIcon();
}

auto Resources::loadIcon() -> void {
    if (!icon.loadFromFile("../materials/images/MonkeyTyperPicture.png")) {
        std::cerr << "Couldn't load icon.\n";
    }
}

auto Resources::loadFonts() -> void {
    sf::Font bloxFont;
    if (!bloxFont.openFromFile("../materials/fonts/Blox.ttf")) {
        std::cerr << "Couldn't load bloxFont\n";
    }
    fonts["BloxFont"] = std::move(bloxFont);

    sf::Font pixelFont;
    if (!pixelFont.openFromFile("../materials/fonts/Pixel.ttf")) {
        std::cerr << "Couldn't load pixelFont\n";
    }
    fonts["PixelFont"] = std::move(pixelFont);

    sf::Font alphbetaFont;
    if (!alphbetaFont.openFromFile("../materials/fonts/Alphbeta.ttf")) {
        std::cerr << "Couldn't load alphbetaFont\n";
    }
    fonts["AlphbetaFont"] = std::move(alphbetaFont);

    sf::Font hevillaFont;
    if (!hevillaFont.openFromFile("../materials/fonts/Hevilla.ttf")) {
        std::cerr << "Couldn't load hefillaFont\n";
    }
    fonts["HevillaFont"] = std::move(hevillaFont);

    sf::Font steveFont;
    if (!steveFont.openFromFile("../materials/fonts/Steve.ttf")) {
        std::cerr << "Couldn't load steveFont\n";
    }
    fonts["SteveFont"] = std::move(steveFont);

    sf::Font warworkFont;
    if (!warworkFont.openFromFile("../materials/fonts/Warwork.ttf")) {
        std::cerr << "Couldn't load warworkFont\n";
    }
    fonts["WarworkFont"] = std::move(warworkFont);

    sf::Font grosacFont;
    if (!grosacFont.openFromFile("../materials/fonts/Grosac.ttf")) {
        std::cerr << "Couldn't load grosacFont\n";
    }
    fonts["GrosacFont"] = std::move(grosacFont);
}

auto Resources::loadMusic() -> void {
    if (!backgroundMusic.openFromFile("../materials/music/musicGame.mp3")) { //
        std::cerr << "Couldn't load background music\n";
    }
    backgroundMusic.setLooping(true);
}

auto Resources::loadTypeSound() -> void {
    if (!typeBuffer.loadFromFile("../materials/soundEffect/typeSound.ogg")) {
        std::cerr << "Couldn't load typeSound\n";
    }
    typeSound.setBuffer(typeBuffer);
}

auto Resources::getFont(const std::string& name) ->  sf::Font&  {
    return fonts[name];
}

auto Resources::getMusic() -> sf::Music&{
    return backgroundMusic;
}

auto Resources::getTypeSound() -> sf::Sound& {
    return typeSound;
}

auto Resources::switchMusic() -> void {
    sf::Music& music = getMusic();
    if (music.getStatus() == sf::SoundSource::Status::Playing){
        music.pause();
    } else {
        music.play();
    }
}

auto Resources::typeSoundPlay() -> void {
    typeSound.stop();
    typeSound.play();
}

auto Resources::setIcon(sf::RenderWindow& window) -> void {
    window.setIcon(icon);
}