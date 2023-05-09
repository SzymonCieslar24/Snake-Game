#include "Snake.h"

void Snake::initSnake() {
	snakeBody.resize(3);
	snakeHead = snakeBody.begin();
	snakeTail = std::prev(snakeBody.end());
	snakeBodyTex.loadFromFile("textures/snake.png");
	snakeHeadTex.loadFromFile("textures/snakeHead.png");
	snakeTailTex.loadFromFile("textures/snakeTail.png");
	snakeHead->setTexture(snakeHeadTex);
	startPos = { 96, 64 };
	snakeHead->setPosition(startPos);
	float yPos = startPos.y;
	for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
		piece.setTexture(snakeBodyTex);
		piece.setPosition({ 96, yPos });
		yPos += 32;
	}
	snakeTail->setTexture(snakeTailTex);
	snakeTail->setPosition(96, yPos);
}
void Snake::drawSnake(sf::RenderWindow &window) 
{
	for (auto& piece : snakeBody)
	{
		window.draw(piece);
	}
}
void Snake::moveSnake(sf::Vector2f& moveDirection)
{
	oldHeadPos = snakeHead->getPosition();
	snakeHead->setPosition(snakeHead->getPosition() + moveDirection);
	for (auto& piece : snakeBody | std::views::drop(1)) {
		sf::Vector2f tmpOldPos = piece.getPosition();
		piece.setPosition(oldHeadPos);
		oldHeadPos = tmpOldPos;
	}
}
void Snake::growSnake() 
{

}
bool Snake::isSnakeOnSmth(sf::Sprite &something)
{

}
bool Snake::isSelfEating() 
{

}