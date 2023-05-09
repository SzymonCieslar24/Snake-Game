#include "Game.h"

void Game::startGame() {
	sf::RenderWindow window(sf::VideoMode(1920, 1088), "Snake Game", sf::Style::Close);
	ResourcesMan::loadFont("fonts/Pacifico-Regular.ttf", "primary");
	Main_menu menu;
	menu.show_menu(window);
}

void Game::initMap(sf::RenderWindow &window) {
	wall_tex.loadFromFile("textures/wall.png");
	grass_tex.loadFromFile("textures/grass.png");
	wall_tex.setRepeated(true);
	grass_tex.setRepeated(true);
	grass.setTexture(grass_tex);
	int windowX = (int)window.getSize().x;
	int windowY = (int)window.getSize().y;
	for (int i = 0; i < walls.size(); i++) 
	{
		walls[i].setTexture(wall_tex);
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

void Game::update(sf::Time& time) {
	pastTime += time;
	if (pastTime.asSeconds() > 2)
	{
		//for (auto& wall : m_walls)
		//{
		//	if (m_snake.IsOn(wall))
		//	{
		//		m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
		//		break;
		//	}
		//}

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
		snake.moveSnake(snakeDirection);

		//if (m_snake.IsSelfIntersecting())
		//{
		//	m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
		//}

		pastTime = sf::Time::Zero;
	}
}

void Game::gameOptions(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		update(timePerFrame);
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (e.type == sf::Event::KeyPressed)
			{
				sf::Vector2f newDirection = snakeDirection;
				switch (e.key.code)
				{
				case sf::Keyboard::Up:
					newDirection = { 0.f, -32.f };
					break;
				case sf::Keyboard::Down:
					newDirection = { 0.f, 32.f };
					break;
				case sf::Keyboard::Left:
					newDirection = { -32.f, 0.f };
					break;
				case sf::Keyboard::Right:
					newDirection = { 32.f, 0.f };
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
