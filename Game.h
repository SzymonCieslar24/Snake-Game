#pragma once

#include <iostream>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Apple.h"
#include "Banana.h"
#include "Orange.h"
#include "Strawberry.h"

class Game {
private:
	sf::Sprite grass;
	std::array<sf::Sprite, 4> walls;
	sf::Text scoreText;
	sf::Text timeText;
	sf::Text pauseText;
	sf::Text pauseInfo;
	sf::Clock clk;
	sf::Time gameTime;
	sf::Time pauseTime;
	sf::Time pauseStart;
	static int score;
	bool isPaused;
	bool isReverse;
	bool isImmune;
	float speed;
	sf::Time pastTime;
	sf::Time timePerFrame;
	sf::Vector2f snakeDirection;
	Snake snake;
	Apple* applePtr;
	Banana* bananaPtr;
	Orange* orangePtr;
	Strawberry* strawberryPtr;
	Fruit* fruitPtr;
public:
	void startGame();
	void initMap(sf::RenderWindow& window);
	void drawWalls(sf::RenderWindow& window);
	void update(sf::Time& time, sf::RenderWindow& window);
	sf::Vector2f& generateFruitPos(sf::RenderWindow& window);
	void timeInGame();
	static int& getScore();
	void gameOptions(sf::RenderWindow& window);
};