#pragma once

#include <array>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

class ResourcesMan {
private:
	static sf::Font primary;
	static sf::Font secondary;
	static std::array<sf::Texture, 3>  snakeTexUp;
	static std::array<sf::Texture, 3>  snakeTexDown;
	static std::array<sf::Texture, 3>  snakeTexRight;
	static std::array<sf::Texture, 3>  snakeTexLeft;
	static sf::Texture grassTex;
	static sf::Texture wallTex;
public:
	static void loadFont(const std::string& filename,const std::string& fontname);
	static sf::Font& getFont(const std::string& name);
	static void loadTexture(const std::string& filename, const std::string& fontname);
	static sf::Font& getTexture(const std::string& name);
};