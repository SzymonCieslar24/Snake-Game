#include "Game.h"
int Game::score;

void Game::startGame() {
	sf::RenderWindow window(sf::VideoMode(1920, 1088), "Snake Game", sf::Style::Close);
	ResourcesMan::loadFont("fonts/Sriracha-Regular.ttf", "primary");
	ResourcesMan::loadFont("fonts/ShantellSans-Regular.ttf", "secondary");
	ResourcesMan::loadBoardTexture("textures/wall.png");
	ResourcesMan::loadBoardTexture("textures/grass.png");
	ResourcesMan::loadBoardTexture("textures/apple.png");
	ResourcesMan::loadBoardTexture("textures/banana.png");
	ResourcesMan::loadBoardTexture("textures/orange.png");
	ResourcesMan::loadBoardTexture("textures/strawberry.png");
	ResourcesMan::loadSnakeTexture("textures/snakeHeadUp.png", "textures/snakeBodyUpDown.png", "textures/snakeTailUp.png", ResourcesMan::Up);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadRight.png", "textures/snakeBodyLeftRight.png", "textures/snakeTailRight.png", ResourcesMan::Right);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadDown.png", "textures/snakeBodyUpDown.png", "textures/snakeTailDown.png", ResourcesMan::Down);
	ResourcesMan::loadSnakeTexture("textures/snakeHeadLeft.png", "textures/snakeBodyLeftRight.png", "textures/snakeTailLeft.png", ResourcesMan::Left);
	Main_menu menu;
	menu.show_menu(window);
}

void Game::initMap(sf::RenderWindow &window) {
	isPaused = false;
	isReverse = false;
	isImmune = false;
	score = 0;
	speed = 90.f;
	pastTime = sf::Time::Zero;
	timePerFrame = sf::seconds(1.f / speed);
	snakeDirection = { 0.f, -32.f };
	applePtr = new Apple;
	bananaPtr = new Banana;
	orangePtr = new Orange;
	strawberryPtr = new Strawberry;
	fruitPtr = applePtr;
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(40);
	scoreText.setFont(ResourcesMan::getFont("primary"));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(48.f, 0);
	timeText.setCharacterSize(40);
	timeText.setFont(ResourcesMan::getFont("primary"));
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(window.getSize().x - 375.f, 0);
	pauseText.setString("Paused");
	pauseText.setCharacterSize(120);
	pauseText.setFont(ResourcesMan::getFont("primary"));
	pauseText.setFillColor(sf::Color::Green);
	pauseText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	pauseText.setOrigin(pauseText.getLocalBounds().left + pauseText.getLocalBounds().width / 2.0f, pauseText.getLocalBounds().top + pauseText.getLocalBounds().height / 2.0f);
	pauseInfo.setString("Press escape to pause the game.");
	pauseInfo.setCharacterSize(40);
	pauseInfo.setFont(ResourcesMan::getFont("primary"));
	pauseInfo.setFillColor(sf::Color::White);
	pauseInfo.setPosition(window.getSize().x / 2.0f, 0);
	pauseInfo.setOrigin(pauseInfo.getLocalBounds().left + pauseInfo.getLocalBounds().width / 2.0f, 0);
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
	fruitPtr->getFruit().setPosition(generateFruitPos(window));
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
	if (pastTime.asSeconds() > 1.5)
	{
		for (auto& wall : walls)
		{
			if (snake.isSnakeOnSmth(wall)) {
				GameOver g;
				g.show_gameOver(window);
				break;
			}
		}
		if (snake.isSelfEating() && !isImmune)
		{
			GameOver g;
			g.show_gameOver(window);
		}
		if (snake.isSnakeOnSmth(fruitPtr -> getFruit()))
		{
			fruitPtr->effect(snake, score, speed, isReverse, isImmune);
			timePerFrame = sf::seconds(1.f / speed);
			std::srand(std::time(0));
			int randNum = std::rand() % 101;
			std::array<int,2> appleP = Apple::getProbability(score);
			std::array<int, 2> bananaP= Banana::getProbability(score);
			std::array<int, 2> orangeP = Orange::getProbability(score);
			std::array<int, 2> strawberryP = Strawberry::getProbability(score);
			if (randNum>=appleP[0] && randNum < appleP[1]) {
				fruitPtr = applePtr;
			}
			else if (randNum >= bananaP[0] && randNum < bananaP[1]) {
				fruitPtr = bananaPtr;
			}
			else if (randNum >= orangeP[0] && randNum < orangeP[1]) {
				fruitPtr = orangePtr;
			}
			else if (randNum >= strawberryP[0] && randNum < strawberryP[1]) {
				fruitPtr = strawberryPtr;
			}
			scoreText.setString("Score: " + std::to_string(score));
			fruitPtr->getFruit().setPosition(generateFruitPos(window));
		}
		snake.moveSnake(snakeDirection);
		pastTime = sf::Time::Zero;
	}
}

sf::Vector2f& Game::generateFruitPos(sf::RenderWindow& window) {
	sf::Vector2f fruitPos;
	float x = 48, y = 48;
	float grassX = window.getSize().x - 2 * 48.f;
	float grassY = window.getSize().y - 2 * 48.f;
	int grassXPos = grassX / 32;
	int grassYPos = grassY / 32;
	std::srand(std::time(0));
	int randX = std::rand() % grassXPos;
	int randY = std::rand() % grassYPos;
	x += 32 * randX;
	y += 32 * randY;
	fruitPos.x = x;
	fruitPos.y = y;
	return fruitPos;
}

void Game::timeInGame() {
	gameTime = clk.getElapsedTime() - pauseTime;
	int seconds = gameTime.asSeconds();
	int minutes = seconds / 60;
	seconds %= 60;
	timeText.setString("Time in game: " + std::to_string(minutes) + ":" + std::to_string(seconds));
}

int Game::getScore() {
	return score;
}

void Game::gameOptions(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		if (!isPaused) {
			update(timePerFrame, window);
			timeInGame();
		}
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
					if (isPaused) {
						isPaused = false;
						pauseTime += clk.getElapsedTime() - pauseStart;
					}
					else {
						isPaused = true;
						pauseStart = clk.getElapsedTime();
					}
					break;
				}
				if (std::abs(snakeDirection.x) != std::abs(newDirection.x) ||
					std::abs(snakeDirection.y) != std::abs(newDirection.y))
				{
					if (isReverse) {
						newDirection.x *= -1;
						newDirection.y *= -1;
					}
					snakeDirection = newDirection;
				}
			}
		}
		window.clear();
		window.draw(grass);
		drawWalls(window);
		window.draw(scoreText);
		window.draw(timeText);
		fruitPtr->drawFruit(window);
		snake.drawSnake(window);
		pauseInfo.setString("Press escape to pause the game.");
		if (isPaused) {
			pauseInfo.setString("Press escape to return to game.");
			window.draw(pauseText);
		}
		window.draw(pauseInfo);
		window.display();
	}
}
