#include "ResourcesManager.h"

sf::Font ResourcesMan::primary;
sf::Font ResourcesMan::secondary;
std::array<sf::Texture, 3> ResourcesMan::snakeTexUp;
std::array<sf::Texture, 3> ResourcesMan::snakeTexRight;
std::array<sf::Texture, 3> ResourcesMan::snakeTexDown;
std::array<sf::Texture, 3> ResourcesMan::snakeTexLeft;
sf::Texture ResourcesMan::grassTex;
sf::Texture ResourcesMan::wallTex;
sf::Texture ResourcesMan::snakeHeadTex;
sf::Texture ResourcesMan::snakeBodyTex;
sf::Texture ResourcesMan::snakeTailTex;

void ResourcesMan::loadFont (const std::string& filename, const std::string& name) {
    if (!std::filesystem::exists(filename)) {
        std::cout << "Font file not found: " << filename << std::endl;
        return;
    }

    sf::Font font;
    if (!font.loadFromFile(filename)) {
        std::cout << "Failed to load font: " << filename << std::endl;
        return;
    }

    if (name == "primary") {
        primary = font;
    }
    else if (name == "secondary") {
        secondary = font;
    }
    else {
        std::cout << "Invalid font name: " << name << std::endl;
    }
}

sf::Font& ResourcesMan::getFont(const std::string& name) {
    if (name == "primary") {
        return primary;
    }
    else if (name == "secondary") {
        return secondary;
    }
    std::cout << "Font not found: " << name << std::endl;
    return primary;
}

void ResourcesMan::loadTexture(const std::string& filename, sf::Texture& tex) {
    if (!std::filesystem::exists(filename)) {
        std::cout << "Texture file not found: " << filename << std::endl;
        return;
    }
    if (!tex.loadFromFile(filename)) {
        std::cout << "Failed to load texture: " << filename << std::endl;
        return;
    }
}
void ResourcesMan::loadBoardTexture (const std::string& filename, const std::string& name) {
    if (name == "grassTex") {
        loadTexture(filename, grassTex);
        grassTex.setRepeated(true);
    }
    else if (name == "wallTex") {
        loadTexture(filename, wallTex);
        wallTex.setRepeated(true);
    }
    else {
        std::cout << "Invalid texture name: " << name << std::endl;
    }
}

sf::Texture& ResourcesMan::getBoardTexture(const std::string& name) {
    if (name == "grassTex") {
        return grassTex;
    }
    else if (name == "wallTex") {
        return wallTex;
    }
    std::cout << "Texture not found: " << name << std::endl;
}

void ResourcesMan::loadSnakeTexture(const std::string& snakeHead, const std::string& snakeBody, const std::string& snakeTail, Direction dir) {
    loadTexture(snakeHead, snakeHeadTex);
    loadTexture(snakeBody, snakeBodyTex);
    loadTexture(snakeTail, snakeTailTex);
    switch (dir) {
    case Up:
        snakeTexUp[0] = snakeHeadTex;
        snakeTexUp[1] = snakeBodyTex;
        snakeTexUp[2] = snakeTailTex;
    case Right:
        snakeTexRight[0] = snakeHeadTex;
        snakeTexRight[1] = snakeBodyTex;
        snakeTexRight[2] = snakeTailTex;
    case Down:
        snakeTexDown[0] = snakeHeadTex;
        snakeTexDown[1] = snakeBodyTex;
        snakeTexDown[2] = snakeTailTex;
    case Left:
        snakeTexLeft[0] = snakeHeadTex;
        snakeTexLeft[1] = snakeBodyTex;
        snakeTexLeft[2] = snakeTailTex;
    }
}
std::array<sf::Texture, 3>& ResourcesMan::getSnakeTexture(const std::string& name) {
    if (name == "snakeTexUp") {
        return snakeTexUp;
    }
    else if (name == "snakeTexRight") {
        return snakeTexRight;
    }
    else if (name == "snakeTexDown") {
        return snakeTexDown;
    }
    else if (name == "snakeTexLeft") {
        return snakeTexLeft;
    }
    std::cout << "Textures array not found: " << name << std::endl;
}