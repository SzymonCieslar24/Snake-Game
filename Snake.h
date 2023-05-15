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
	sf::Vector2f oldHeadPos;
	std::list<sf::Sprite> snakeBody;
	std::list<sf::Sprite>::iterator snakeHead;
	std::list<sf::Sprite>::iterator snakeTail;
public:
	void initSnake();
	void drawSnake(sf::RenderWindow &window);
	void moveSnake(sf::Vector2f &moveDirection, ResourcesMan::Direction dir);
	void updateTextures(ResourcesMan::Direction dir);
	void growSnake();
	bool isSnakeOnSmth(sf::Sprite &something);
	bool isSelfEating();
};