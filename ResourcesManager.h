#pragma once

#include <array>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

class ResourcesMan {
private:
	static sf::Font primary;
	static sf::Font secondary;
	static std::array<sf::Texture, 3> snakeTexUp;
	static std::array<sf::Texture, 3> snakeTexRight;
	static std::array<sf::Texture, 3> snakeTexDown;
	static std::array<sf::Texture, 3> snakeTexLeft;
	static sf::Texture grassTex;
	static sf::Texture wallTex;
	static sf::Texture appleTex;
	static sf::Texture bananaTex;
	static sf::Texture orangeTex;
	static sf::Texture snakeHeadTex;
	static sf::Texture snakeBodyTex;
	static sf::Texture snakeTailTex;
public:
	enum Direction {
		Up,
		Right,
		Down,
		Left
	};
	enum snakeParts {
		Head,
		Body,
		Tail
	};
	static void loadFont(const std::string& filename, const std::string& fontname);
	static sf::Font& getFont(const std::string& name);
	static void loadTexture(const std::string& filename, sf::Texture& tex);
	static void loadBoardTexture(const std::string& filename, const std::string& fontname);
	static sf::Texture& getBoardTexture(const std::string& name);
	static void loadSnakeTexture(const std::string& snakeHead, const std::string& snakeBody, const std::string& snakeTail, Direction dir);
	static std::array<sf::Texture, 3>& getSnakeTexture(Direction dir);
};