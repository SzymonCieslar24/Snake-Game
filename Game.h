#pragma once

#include <iostream>
#include <memory>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"
#include "GameOver.h"

import ResourcesManager;
import Snake;
import Fruit;
import Apple;
import Banana;
import Orange;
import Strawberry;

class Game : public Scene {
private:
	sf::Sprite grass;
	std::array<sf::Sprite, 4> walls;
	Snake snake;
	sf::Text scoreTxt;
	sf::Text timeTxt;
	sf::Text pauseTxt;
	sf::Text pauseInfoTxt;
	sf::Clock clk;
	sf::Time gameTime;
	sf::Time pauseTime;
	sf::Time pauseStart;
	sf::Time pastTime;
	sf::Time timePerFrame;
	static int score;
	bool isPaused;
	bool isReverse;
	bool isImmune;
	float speed;
	sf::Vector2f snakeDirection;
	std::unique_ptr<Fruit> fruitPtr;
	std::unique_ptr<Scene> scenePtr;
public:
	Game();
	void startGame();
	virtual void setScene(sf::RenderWindow& window);
	void drawWalls(sf::RenderWindow& window);
	void update(sf::Time& time, sf::RenderWindow& window);
	static int& getScore();
	sf::Vector2f& generateFruitPos(sf::RenderWindow& window);
	void timeInGame();
	virtual void windowHandle(sf::RenderWindow& window);
};