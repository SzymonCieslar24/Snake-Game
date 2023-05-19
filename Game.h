#pragma once

#include <iostream>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Fruit.h"
#include "Apple.h"
#include "Banana.h"

class Game {
private:
	sf::Sprite grass;
	std::array<sf::Sprite, 4> walls;
	sf::Text scoreText;
	sf::Text timeText;
	sf::Clock clk;
	sf::Time gameTime;
	int score = 0;
	sf::Time pastTime = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Vector2f snakeDirection = { 0.f, -32.f };
	Snake snake;
	Apple* applePtr = new Apple;
	Banana* bananaPtr = new Banana;
	Fruit* fruitPtr = bananaPtr;
public:
	void startGame();
	void initMap(sf::RenderWindow& window);
	void drawWalls(sf::RenderWindow& window);
	void update(sf::Time& time, sf::RenderWindow& window);
	void gameOptions(sf::RenderWindow& window);
};