#pragma once

#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "MainMenu.h"
#include "ResourcesManager.h"

class Game {
private:
	sf::Texture grass_tex;
	sf::Texture wall_tex;
	sf::Sprite grass;
	sf::Time pastTime = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Vector2f snakeDirection = { 32.f, 0.f };
	std::array<sf::Sprite, 4> walls;
	Snake snake;
public:
	void startGame();
	void initMap(sf::RenderWindow& window);
	void drawWalls(sf::RenderWindow& window);
	void update(sf::Time& time);
	void gameOptions(sf::RenderWindow& window);
};