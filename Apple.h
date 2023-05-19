#pragma once

#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "ResourcesManager.h"

class Apple : public Fruit {
private:
	sf::Sprite apple;
public:
	virtual void generate(sf::RenderWindow& window);
	virtual void drawFruit(sf::RenderWindow& window);
	virtual sf::Sprite& getFruit();
	virtual void effect(Snake& snake, int& score);
	static std::array<int,2> getProbability(int& score);
};