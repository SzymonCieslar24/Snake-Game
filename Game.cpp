#include "Game.h"

void Game::startGame() {
	sf::RenderWindow window(sf::VideoMode(1920, 1088), "Snake Game", sf::Style::Close);
	ResourcesMan::loadFont("fonts/Sriracha-Regular.ttf", "primary");
	ResourcesMan::loadFont("fonts/ShantellSans-Regular.ttf", "secondary");
	ResourcesMan::loadBoardTexture("textures/wall.png", "wall");
	ResourcesMan::loadBoardTexture("textures/grass.png", "grass");
	ResourcesMan::loadBoardTexture("textures/apple.png", "apple");
	ResourcesMan::loadBoardTexture("textures/banana.png", "banana");
	ResourcesMan::loadBoardTexture("textures/orange.png", "orange");
	ResourcesMan::loadSnakeTexture("textures/snakeHeadUp.png", "textures/snakeBodyUpDown.png", "textures/snakeTailUp.png", ResourcesMan::Up);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadRight.png", "textures/snakeBodyLeftRight.png", "textures/snakeTailRight.png", ResourcesMan::Right);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadDown.png", "textures/snakeBodyUpDown.png", "textures/snakeTailDown.png", ResourcesMan::Down);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadLeft.png", "textures/snakeBodyLeftRight.png", "textures/snakeTailLeft.png", ResourcesMan::Left);
	Main_menu menu;
	menu.show_menu(window);
}

void Game::initMap(sf::RenderWindow &window) {
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(40);
	scoreText.setFont(ResourcesMan::getFont("primary"));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(48.f, 0);
	timeText.setCharacterSize(40);
	timeText.setFont(ResourcesMan::getFont("primary"));
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(window.getSize().x - 375.f, 0);
	grass.setTexture(ResourcesMan::getBoardTexture("grass"));
	int windowX = (int)window.getSize().x;
	int windowY = (int)window.getSize().y;
	for (int i = 0; i < walls.size(); i++) 
	{
		walls[i].setTexture(ResourcesMan::getBoardTexture("wall"));
	}
	grass.setTextureRect({ 0,0, windowX, windowY });
	walls[0].setTextureRect({0,0, windowX, 48});
	walls[1].setTextureRect({48,0, windowX, 48});
	walls[1].setPosition(0, windowY - 48);
	walls[2].setTextureRect({0,0, 48, windowY });
	walls[3].setTextureRect({0,0, 48, windowY });
	walls[3].setPosition(windowX - 48, 0);
	snake.initSnake();
	fruitPtr->generate(window);
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
		if (snake.isSnakeOnSmth(fruitPtr -> getFruit()))
		{
			std::srand(std::time(0));
			int randNum = std::rand() % 101; // Losowanie liczby od 0 do 100
			std::cout << randNum << std::endl;
			std::array<int,2> appleP = Apple::getProbability(score);
			std::array<int, 2> bananaP= Banana::getProbability(score);
			std::cout << appleP[0] << " " << appleP[1] << std::endl;
			if (randNum>=appleP[0] && randNum < appleP[1]) {
				fruitPtr = applePtr;
				std::cout << "Apple" << std::endl;
			}
			else if (randNum >= bananaP[0] && randNum < bananaP[1]) {
				fruitPtr = bananaPtr;
				std::cout << "Banana" << std::endl;
			}
			fruitPtr->generate(window);
			fruitPtr->effect(snake, score);
			scoreText.setString("Score: " + std::to_string(score));
		}
		snake.moveSnake(snakeDirection);
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
				switch (e.key.code)
				{
				case sf::Keyboard::Up:
					newDirection = { 0.f, -32.f };
					break;
				case sf::Keyboard::W:
					newDirection = { 0.f, -32.f };
					break;
				case sf::Keyboard::Down:
					newDirection = { 0.f, 32.f };
					break;
				case sf::Keyboard::S:
					newDirection = { 0.f, 32.f };
					break;
				case sf::Keyboard::Left:
					newDirection = { -32.f, 0.f };
					break;
				case sf::Keyboard::A:
					newDirection = { -32.f, 0.f };
					break;
				case sf::Keyboard::Right:
					newDirection = { 32.f, 0.f };
					break;
				case sf::Keyboard::D:
					newDirection = { 32.f, 0.f };
					break;
				case sf::Keyboard::Escape:
					//To do: 
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
		gameTime = clk.getElapsedTime();
		int seconds = gameTime.asSeconds();
		int minutes = seconds / 60;
		seconds %= 60;
		timeText.setString("Time in game: " + std::to_string(minutes) + ":" + std::to_string(seconds));
		window.clear();
		window.draw(grass);
		drawWalls(window);
		window.draw(scoreText);
		window.draw(timeText);
		fruitPtr->drawFruit(window);
		snake.drawSnake(window);
		window.display();
	}
}
