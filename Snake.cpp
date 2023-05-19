#include "Snake.h"

void Snake::initSnake() {
	snakeBody.resize(snakeSize);
	snakeHead = snakeBody.begin();
	snakeTail = std::prev(snakeBody.end());
	startPos = { 944, 624 };
	startDir = ResourcesMan::Up;
	snakeHead->setPosition(startPos);
	snakeHead->setTexture(ResourcesMan::getSnakeTexture(startDir)[ResourcesMan::Head]);
	startPos.y += 32;
	for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
		piece.setPosition(startPos);
		piece.setTexture(ResourcesMan::getSnakeTexture(startDir)[ResourcesMan::Body]);
		startPos.y += 32;
	}
	snakeTail->setPosition(startPos);
	snakeTail->setTexture(ResourcesMan::getSnakeTexture(startDir)[ResourcesMan::Tail]);
}
void Snake::drawSnake(sf::RenderWindow& window)
{
	for (auto& piece : snakeBody)
	{
		window.draw(piece);
	}
}

ResourcesMan::Direction Snake::getPieceDirection(sf::Vector2f Position, sf::Vector2f& Position2) {
	if (Position.x == Position2.x && Position.y > Position2.y)
		return ResourcesMan::Up;
	else if (Position.x < Position2.x && Position.y == Position2.y)
		return ResourcesMan::Right;
	else if (Position.x == Position2.x && Position.y < Position2.y)
		return ResourcesMan::Down;
	else if (Position.x > Position2.x && Position.y == Position2.y)
		return ResourcesMan::Left;
}

void Snake::moveSnake(sf::Vector2f& moveDirection)
{
	sf::Vector2f oldHeadPos = snakeHead->getPosition();
	snakeHead->setPosition(snakeHead->getPosition() + moveDirection);
	sf::Vector2f newHeadPos = snakeHead->getPosition();
	ResourcesMan::Direction oldHeadDir = getPieceDirection(oldHeadPos, newHeadPos);
	snakeHead->setTexture(ResourcesMan::getSnakeTexture(oldHeadDir)[ResourcesMan::Head]);
	for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
		sf::Vector2f tmpOldPos = piece.getPosition();
		ResourcesMan::Direction tmpOldDir = getPieceDirection(tmpOldPos, oldHeadPos);
		piece.setPosition(oldHeadPos);
		piece.setTexture(ResourcesMan::getSnakeTexture(oldHeadDir)[ResourcesMan::Body]);
		oldHeadPos = tmpOldPos;
		oldHeadDir = tmpOldDir;
	}
	snakeTail->setPosition(oldHeadPos);
	snakeTail->setTexture(ResourcesMan::getSnakeTexture(oldHeadDir)[ResourcesMan::Tail]);
}
void Snake::growSnake()
{
	snakeSize++;
	snakeBody.resize(snakeSize);
	snakeHead = snakeBody.begin();
	snakeTail = std::prev(snakeBody.end());
}
bool Snake::isSnakeOnSmth(sf::Sprite& something)
{
	return something.getGlobalBounds().intersects(snakeHead->getGlobalBounds());
}
bool Snake::isSelfEating()
{
	bool flag = false;
	for (auto piece = snakeBody.begin(); piece != snakeBody.end(); ++piece)
	{
		if (snakeHead != piece)
		{
			flag = isSnakeOnSmth(*piece);
			if (flag)
			{
				break;
			}
		}
	}
	return flag;
}