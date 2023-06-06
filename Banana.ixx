export module Banana;

import <SFML/Graphics.hpp>;
import Fruit;
import ResourcesManager;

export class Banana : public Fruit {
private:
	sf::Sprite banana;
public:
	virtual void drawFruit(sf::RenderWindow& window);
	virtual sf::Sprite& getFruit();
	virtual void effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune);
	static std::array<int, 2> getProbability(int& score);
};

void Banana::drawFruit(sf::RenderWindow& window) {
    banana.setTexture(ResourcesMan::getBoardTexture("banana"));
    window.draw(banana);
}

sf::Sprite& Banana::getFruit() {
    return banana;
}
void Banana::effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune) {
    snake.growSnake();
    snake.growSnake();
    score += 12;
    isReverse = false;
    isImmune = false;
    if (speed > 40.f)
        speed -= 10.f;
}

std::array<int, 2> Banana::getProbability(int& score) {
    if (score < 20) {
        return { 0,0 };
    }
    else if (score >= 20 && score < 50) {
        return { 51,90 };
    }
    else if (score >= 50 && score < 100) {
        return { 31,70 };
    }
    else
        return { 21,50 };
}