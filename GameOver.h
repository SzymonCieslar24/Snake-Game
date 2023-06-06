#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"
#include "Game.h"
#include "Save.h"

import Button;

class GameOver : public Scene {
private:
	sf::Text overTxt;
	sf::Text scoreTxt;
	Button playAgainBtn;
	Button saveScoreBtn;
	Button menuBtn;
	std::unique_ptr<Scene> scenePtr;
public:
	GameOver();
	virtual void setScene(sf::RenderWindow& window);
	virtual void windowHandle(sf::RenderWindow& window);
};