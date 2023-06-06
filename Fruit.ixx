export module Fruit;

import <SFML/Graphics.hpp>;

import Snake;

export class Fruit{
public:
	virtual void drawFruit(sf::RenderWindow & window) = 0;
	virtual sf::Sprite& getFruit() = 0;
	virtual void effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune) = 0;
};
