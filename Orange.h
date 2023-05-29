#pragma once

#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "ResourcesManager.h"

class Orange : public Fruit {
private:
	sf::Sprite orange;
public:
	virtual void drawFruit(sf::RenderWindow& window);
	virtual sf::Sprite& getFruit();
	virtual void effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune);
	static std::array<int, 2> getProbability(int& score);
};
