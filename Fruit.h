#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.h"

class Fruit {
public:
	virtual void drawFruit(sf::RenderWindow& window) = 0;
	virtual sf::Sprite& getFruit() = 0;
	virtual void effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune) = 0;
};
