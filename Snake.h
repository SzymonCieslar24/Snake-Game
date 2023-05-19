#pragma once

#include <iostream>
#include <list>
#include <ranges>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"

class Snake {
private:
	sf::Vector2f startPos;
	ResourcesMan::Direction startDir;
	std::list<sf::Sprite> snakeBody;
	std::list<sf::Sprite>::iterator snakeHead;
	std::list<sf::Sprite>::iterator snakeTail;
	int snakeSize = 5;
public:
	void initSnake();
	void drawSnake(sf::RenderWindow& window);
	ResourcesMan::Direction getPieceDirection(sf::Vector2f oldPosition, sf::Vector2f& moveDirection);
	void moveSnake(sf::Vector2f& moveDirection);
	void growSnake();
	bool isSnakeOnSmth(sf::Sprite& something);
	bool isSelfEating();
};