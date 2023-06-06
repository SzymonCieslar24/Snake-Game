#include "Game.h"

int Game::score = 0;

Game::Game() :
	isPaused(false),
	isReverse(false),
	isImmune(false),
	speed(80.f),
	pastTime(sf::Time::Zero),
	snakeDirection(0.f, -32.f),
	fruitPtr(std::make_unique<Apple>()),
	scenePtr(nullptr),
	grass(ResourcesMan::getBoardTexture("grass")),
	scoreTxt("", ResourcesMan::getFont("primary"), 40),
	pauseTxt("Paused", ResourcesMan::getFont("primary"), 120),
	timeTxt("", ResourcesMan::getFont("primary"), 40),
	pauseInfoTxt("Press escape to pause the game.", ResourcesMan::getFont("primary"), 40)
{
	score = 0;
	pauseTxt.setFillColor(sf::Color::Green);
	pauseTxt.setOrigin(pauseTxt.getLocalBounds().left + pauseTxt.getLocalBounds().width / 2.0f, pauseTxt.getLocalBounds().top + pauseTxt.getLocalBounds().height / 2.0f);
	scoreTxt.setFillColor(sf::Color::White);
	timeTxt.setFillColor(sf::Color::White);
	pauseInfoTxt.setFillColor(sf::Color::White);
	pauseInfoTxt.setOrigin(pauseInfoTxt.getLocalBounds().left + pauseInfoTxt.getLocalBounds().width / 2.0f, 0);
}

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
	scenePtr = std::make_unique<Main_menu>();
	scenePtr->setScene(window);
}

void Game::setScene(sf::RenderWindow &window) {
	timePerFrame = sf::seconds(1.f / speed);
	scoreTxt.setString("Score: " + std::to_string(score));
	scoreTxt.setPosition(48.f, 0);
	timeTxt.setPosition(window.getSize().x - 375.f, 0);
	pauseTxt.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	pauseInfoTxt.setPosition(window.getSize().x / 2.0f, 0);
	fruitPtr->getFruit().setPosition(generateFruitPos(window));
	windowHandle(window);
}

void Game::drawWalls(sf::RenderWindow& window) {
	int windowX = (int)window.getSize().x;
	int windowY = (int)window.getSize().y;
	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].setTexture(ResourcesMan::getBoardTexture("wall"));
	}
	grass.setTextureRect({ 0,0, windowX, windowY });
	walls[0].setTextureRect({ 0,0, windowX, 48 });
	walls[1].setTextureRect({ 48,0, windowX, 48 });
	walls[1].setPosition(0, windowY - 48);
	walls[2].setTextureRect({ 0,0, 48, windowY });
	walls[3].setTextureRect({ 0,0, 48, windowY });
	walls[3].setPosition(windowX - 48, 0);
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
			if (snake.isSnakeOnSmth(wall)) 
			{
				scenePtr = std::make_unique<GameOver>();
				scenePtr -> setScene(window);
				break;
			}
		}
		if (snake.isSelfEating() && !isImmune)
		{
			scenePtr = std::make_unique<GameOver>();
			scenePtr->setScene(window);
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
				fruitPtr = std::make_unique<Apple>();
			}
			else if (randNum >= bananaP[0] && randNum < bananaP[1]) {
				fruitPtr = std::make_unique<Banana>();
			}
			else if (randNum >= orangeP[0] && randNum < orangeP[1]) {
				fruitPtr = std::make_unique<Orange>();
			}
			else if (randNum >= strawberryP[0] && randNum < strawberryP[1]) {
				fruitPtr = std::make_unique<Strawberry>();
			}
			scoreTxt.setString("Score: " + std::to_string(score));
			fruitPtr->getFruit().setPosition(generateFruitPos(window));
		}
		snake.moveSnake(snakeDirection);
		pastTime = sf::Time::Zero;
	}
}

int& Game::getScore() {
	return score;
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
	timeTxt.setString("Time in game: " + std::to_string(minutes) + ":" + std::to_string(seconds));
}

void Game::windowHandle(sf::RenderWindow& window) {
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
	window.draw(scoreTxt);
	window.draw(timeTxt);
	fruitPtr->drawFruit(window);
	snake.drawSnake(window);
	pauseInfoTxt.setString("Press escape to pause the game.");
	if (isPaused) {
		pauseInfoTxt.setString("Press escape to return to game.");
		window.draw(pauseTxt);	
	}
	window.draw(pauseInfoTxt);
	window.display();
	}
}
