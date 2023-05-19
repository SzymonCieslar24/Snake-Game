#include "Banana.h"

void Banana::generate(sf::RenderWindow& window) {
    banana.setTexture(ResourcesMan::getBoardTexture("banana"));
    int x = 0, y = 0;
    x = std::clamp<int>(rand() % window.getSize().x, 32, window.getSize().x - 2 * 48);
    y = std::clamp<int>(rand() % window.getSize().y, 32, window.getSize().y - 2 * 48);
    banana.setPosition(x, y);
}

void Banana::drawFruit(sf::RenderWindow& window) {
    window.draw(banana);
}

sf::Sprite& Banana::getFruit() {
    return banana;
}
void Banana::effect(Snake& snake, int& score) {
    snake.growSnake();
    snake.growSnake();
    score += 12;
}

std::array<int,2> Banana::getProbability(int& score) {
    if (score < 20) {
        return { 0,0 };
    }
    else if (score >= 20 && score < 50) {
        return { 51,100 };
    }
    else if (score >= 50 && score < 100) {
        return { 21,50 };
    }
    else
        return { 11,30 };
}