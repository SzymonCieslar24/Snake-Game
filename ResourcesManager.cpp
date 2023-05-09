#include "ResourcesManager.h"

sf::Font ResourcesMan::primary;
sf::Font ResourcesMan::secondary;
std::array<sf::Texture, 3>  snakeTexUp;
std::array<sf::Texture, 3>  snakeTexDown;
std::array<sf::Texture, 3>  snakeTexRight;
std::array<sf::Texture, 3>  snakeTexLeft;
sf::Texture grass_tex;
sf::Texture wall_tex;

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
    // Return a default font if the requested name is not found
    std::cout << "Font not found: " << name << std::endl;
    return primary;
}

void ResourcesMan::loadTexture (const std::string& filename, const std::string& name) {
    if (!std::filesystem::exists(filename)) {
        std::cout << "Font file not found: " << filename << std::endl;
        return;
    }
    sf::Texture tex;
    if (!tex.loadFromFile(filename)) {
        std::cout << "Failed to load font: " << filename << std::endl;
        return;
    }
    if (name == "grassTex") {
        grassTex = tex;
    }
    else if (name == "wallTex") {
        wallTex = tex;
    }
    else {
        std::cout << "Invalid font name: " << fontname << std::endl;
    }
}

sf::Font& ResourcesMan::getTexture(const std::string& name) {
    if (name == "primary") {
        return primary;
    }
    else if (name == "secondary") {
        return secondary;
    }
    // Return a default font if the requested name is not found
    std::cout << "Font not found: " << name << std::endl;
    return primary;
}