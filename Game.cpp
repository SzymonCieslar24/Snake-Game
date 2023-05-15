#include "Game.h"

void Game::startGame() {
	sf::RenderWindow window(sf::VideoMode(1920, 1088), "Snake Game", sf::Style::Close);
	ResourcesMan::loadFont("fonts/Sriracha-Regular.ttf", "primary");
	ResourcesMan::loadFont("fonts/ShantellSans-Regular.ttf", "secondary");
	ResourcesMan::loadBoardTexture("textures/wall.png", "wallTex");
	ResourcesMan::loadBoardTexture("textures/grass.png", "grassTex");
	ResourcesMan::loadSnakeTexture("textures/snakeHeadUp.png", "textures/snakeBodyUpDown.png", "textures/snakeTailUp.png", ResourcesMan::Up);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadRight.png", "textures/snakeBodyLeftRight.png", "textures/snakeTailRight.png", ResourcesMan::Right);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadDown.png", "textures/snakeBodyUpDown.png", "textures/snakeTailDown.png", ResourcesMan::Down);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadLeft.png", "textures/snakeBodyLeftRight.png", "textures/snakeTailLeft.png", ResourcesMan::Left);
	Main_menu menu;
	menu.show_menu(window);
}

void Game::initMap(sf::RenderWindow &window) {
	grass.setTexture(ResourcesMan::getBoardTexture("grassTex"));
	int windowX = (int)window.getSize().x;
	int windowY = (int)window.getSize().y;
	for (int i = 0; i < walls.size(); i++) 
	{
		walls[i].setTexture(ResourcesMan::getBoardTexture("wallTex"));
	}
	grass.setTextureRect({ 0,0, windowX, windowY });
	walls[0].setTextureRect({0,0, windowX, 32});
	walls[1].setTextureRect({32,0, windowX, 32});
	walls[1].setPosition(0, windowY - 32);
	walls[2].setTextureRect({0,0, 32, windowY });
	walls[3].setTextureRect({0,0, 32, windowY });
	walls[3].setPosition(windowX - 32, 0);
	snake.initSnake();
	gameOptions(window);
}

void Game::drawWalls(sf::RenderWindow& window) {
	for (int i = 0; i < walls.size(); i++)
	{
		window.draw(walls[i]);
	}
}

void Game::update(sf::Time& time, sf::RenderWindow& window) {
	pastTime += time;
	if (pastTime.asSeconds() > 2)
	{
		for (auto& wall : walls)
		{
			if (snake.isSnakeOnSmth(wall)) {
				GameOver g;
				g.show_gameOver(window);
				break;
			}
		}
		if (snake.isSelfEating())
		{
			GameOver g;
			g.show_gameOver(window);
		}
		//if (m_snake.IsOn(m_food))
		//{
		//	m_snake.Grow(m_snakeDirection);

		//	int x = 0, y = 0;
		//	x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
		//	y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

		//	m_food.setPosition(x, y);
		//	m_score += 1;
		//	m_scoreText.setString("Score : " + std::to_string(m_score));
		//}
		snake.moveSnake(snakeDirection, dir);
		pastTime = sf::Time::Zero;
	}
}

void Game::gameOptions(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		update(timePerFrame,window);
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (e.type == sf::Event::KeyPressed)
			{
				sf::Vector2f newDirection = snakeDirection;
				ResourcesMan::Direction newdir = dir;
				switch (e.key.code)
				{
				case sf::Keyboard::Up:
					newDirection = { 0.f, -32.f };
					newdir = ResourcesMan::Up;
					break;
				case sf::Keyboard::Down:
					newDirection = { 0.f, 32.f };
					newdir = ResourcesMan::Down;
					break;
				case sf::Keyboard::Left:
					newDirection = { -32.f, 0.f };
					newdir = ResourcesMan::Left;
					break;
				case sf::Keyboard::Right:
					newDirection = { 32.f, 0.f };
					newdir = ResourcesMan::Right;
					break;
				case sf::Keyboard::Escape:
					//Pause Menu
					break;
				default:
					break;
				}	
				if (std::abs(snakeDirection.x) != std::abs(newDirection.x) ||
					std::abs(snakeDirection.y) != std::abs(newDirection.y))
				{
					snakeDirection = newDirection;
					dir = newdir;
				}
			}
		}
		window.clear();
		window.draw(grass);
		drawWalls(window);
		snake.drawSnake(window);
		window.display();
	}
}
