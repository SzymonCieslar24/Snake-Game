export module Orange;

import <SFML/Graphics.hpp>;
import Fruit;
import ResourcesManager;

export class Orange : public Fruit {
private:
	sf::Sprite orange;
public:
	virtual void drawFruit(sf::RenderWindow& window);
	virtual sf::Sprite& getFruit();
	virtual void effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune);
	static std::array<int, 2> getProbability(int& score);
};

void Orange::drawFruit(sf::RenderWindow& window) {
    orange.setTexture(ResourcesMan::getBoardTexture("orange"));
    window.draw(orange);
}

sf::Sprite& Orange::getFruit() {
    return orange;
}
void Orange::effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune) {
    snake.growSnake();
    score += 20;
    isReverse = true;
    isImmune = false;
    if (speed > 40.f)
        speed -= 3.f;
}

std::array<int, 2> Orange::getProbability(int& score) {
    if (score < 20) {
        return { 0,0 };
    }
    else if (score >= 20 && score < 50) {
        return { 91,100 };
    }
    else if (score >= 50 && score < 100) {
        return { 71,90 };
    }
    else
        return { 51,75 };
}