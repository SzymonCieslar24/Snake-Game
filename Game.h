#pragma once

#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "MainMenu.h"
#include "GameOver.h"

class Game {
private:
	sf::Sprite grass;
	std::array<sf::Sprite, 4> walls;
	sf::Time pastTime = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Vector2f snakeDirection = { 0.f, -32.f };
	ResourcesMan::Direction dir;
	Snake snake;
public:
	void startGame();
	void initMap(sf::RenderWindow& window);
	void drawWalls(sf::RenderWindow& window);
	void update(sf::Time& time, sf::RenderWindow& window);
	void gameOptions(sf::RenderWindow& window);
};