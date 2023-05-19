#include "Apple.h"

void Apple::generate(sf::RenderWindow& window) {
    apple.setTexture(ResourcesMan::getBoardTexture("apple"));
    int x = 0, y = 0;
    x = std::clamp<int>(rand() % window.getSize().x, 32, window.getSize().x - 2 * 48);
    y = std::clamp<int>(rand() % window.getSize().y, 32, window.getSize().y - 2 * 48);
    apple.setPosition(x, y);
}

void Apple::drawFruit(sf::RenderWindow& window) {
    window.draw(apple);
}

sf::Sprite& Apple::getFruit() {
    return apple;
}
void Apple::effect(Snake& snake, int& score) {
    snake.growSnake();
    score += 5;
}

std::array<int, 2> Apple::getProbability(int& score) {
    if (score < 20) {
        return { 0,100 };
    }
    else if (score >= 20 && score < 50) {
        return { 0,50 };
    }
    else if (score >= 50 && score < 100) {
        return { 0,20 };
    }
    else
        return { 0,10 };
}