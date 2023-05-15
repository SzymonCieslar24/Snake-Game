#include "Snake.h"

void Snake::initSnake() {
	snakeBody.resize(7);
	snakeHead = snakeBody.begin();
	snakeTail = std::prev(snakeBody.end());
	startPos = { 960, 640 };
	snakeHead->setPosition(startPos);
	snakeHead->setTexture(ResourcesMan::getSnakeTexture("snakeTexUp")[ResourcesMan::Head]);
	startPos.y += 32;
	for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
		piece.setPosition({startPos});
		piece.setTexture(ResourcesMan::getSnakeTexture("snakeTexUp")[ResourcesMan::Body]);
		startPos.y += 32;
	}
	snakeTail->setPosition({startPos});
	snakeTail->setTexture(ResourcesMan::getSnakeTexture("snakeTexUp")[ResourcesMan::Tail]);
}
void Snake::drawSnake(sf::RenderWindow &window) 
{
	for (auto& piece : snakeBody)
	{
		window.draw(piece);
	}
}
void Snake::moveSnake(sf::Vector2f& moveDirection, ResourcesMan::Direction dir)
{
	oldHeadPos = snakeHead->getPosition();
	snakeHead->setPosition(snakeHead->getPosition() + moveDirection);
	switch (dir)
	{
	case ResourcesMan::Up:
		snakeHead->setTexture(ResourcesMan::getSnakeTexture("snakeTexUp")[ResourcesMan::Head]);
		for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
			sf::Vector2f tmpOldPos = piece.getPosition();
			piece.setPosition(oldHeadPos);
			piece.setTexture(ResourcesMan::getSnakeTexture("snakeTexUp")[ResourcesMan::Body]);
			oldHeadPos = tmpOldPos;
		}
		snakeTail->setPosition(oldHeadPos);
		snakeTail->setTexture(ResourcesMan::getSnakeTexture("snakeTexUp")[ResourcesMan::Tail]);
		break;
	case ResourcesMan::Right:
		snakeHead->setTexture(ResourcesMan::getSnakeTexture("snakeTexRight")[ResourcesMan::Head]);
		for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
			sf::Vector2f tmpOldPos = piece.getPosition();
			piece.setPosition(oldHeadPos);
			piece.setTexture(ResourcesMan::getSnakeTexture("snakeTexRight")[ResourcesMan::Body]);
			oldHeadPos = tmpOldPos;
		}
		snakeTail->setPosition(oldHeadPos);
		snakeTail->setTexture(ResourcesMan::getSnakeTexture("snakeTexRight")[ResourcesMan::Tail]);
		break;
	case ResourcesMan::Down:
		snakeHead->setTexture(ResourcesMan::getSnakeTexture("snakeTexDown")[ResourcesMan::Head]);
		for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
			sf::Vector2f tmpOldPos = piece.getPosition();
			piece.setPosition(oldHeadPos);
			piece.setTexture(ResourcesMan::getSnakeTexture("snakeTexDown")[ResourcesMan::Body]);
			oldHeadPos = tmpOldPos;
		}
		snakeTail->setPosition(oldHeadPos);
		snakeTail->setTexture(ResourcesMan::getSnakeTexture("snakeTexDown")[ResourcesMan::Tail]);
		break;
	case ResourcesMan::Left:
		snakeHead->setTexture(ResourcesMan::getSnakeTexture("snakeTexLeft")[ResourcesMan::Head]);
		for (auto& piece : snakeBody | std::views::drop(1) | std::views::take(snakeBody.size() - 2)) {
			sf::Vector2f tmpOldPos = piece.getPosition();
			piece.setPosition(oldHeadPos);
			piece.setTexture(ResourcesMan::getSnakeTexture("snakeTexLeft")[ResourcesMan::Body]);
			oldHeadPos = tmpOldPos;
		}
		snakeTail->setPosition(oldHeadPos);
		snakeTail->setTexture(ResourcesMan::getSnakeTexture("snakeTexLeft")[ResourcesMan::Tail]);
		break;
	}
}
void Snake::growSnake() 
{

}
bool Snake::isSnakeOnSmth(sf::Sprite &something)
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