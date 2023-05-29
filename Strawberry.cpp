#include "Strawberry.h"

void Strawberry::drawFruit(sf::RenderWindow& window) {
    strawberry.setTexture(ResourcesMan::getBoardTexture("strawberry"));
    window.draw(strawberry);
}

sf::Sprite& Strawberry::getFruit() {
    return strawberry;
}
void Strawberry::effect(Snake& snake, int& score, float& speed, bool& isReverse, bool& isImmune) {
    snake.growSnake();
    score += 15;
    isReverse = false;
    isImmune = true;
    if (speed > 40.f)
        speed += 10.f;
}

std::array<int, 2> Strawberry::getProbability(int& score) {
    if (score < 50) {
        return { 0,0 };
    }
    else if (score >= 50 && score < 100) {
        return { 91,100 };
    }
    else
        return { 76,100 };
}