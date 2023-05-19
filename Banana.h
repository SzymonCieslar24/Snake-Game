#pragma once

#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "ResourcesManager.h"

class Banana : public Fruit {
private:
	sf::Sprite banana;
public:
	virtual void generate(sf::RenderWindow& window);
	virtual void drawFruit(sf::RenderWindow& window);
	virtual sf::Sprite& getFruit();
	virtual void effect(Snake& snake, int& score);
	static std::array<int,2> getProbability(int& score);
};
