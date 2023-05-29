#include "Apple.h"

void Apple::drawFruit(sf::RenderWindow& window) {
    apple.setTexture(ResourcesMan::getBoardTexture("apple"));
    window.draw(apple);
}

sf::Sprite& Apple::getFruit() {
    return apple;
}
void Apple::effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune) {
    snake.growSnake();
    score += 5;
    isReverse = false;
    isImmune = false;
    if (speed > 40.f)
        speed -= 2.f;
}

std::array<int, 2> Apple::getProbability(int& score) {
    if (score < 20) {
        return { 0,100 };
    }
    else if (score >= 20 && score < 50) {
        return { 0,50 };
    }
    else if (score >= 50 && score < 100) {
        return { 0,30 };
    }
    else
        return { 0,20 };
}