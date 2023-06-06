#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Help.h"
#include "Game.h"
#include "Leaderboard.h"

import Button;
import ResourcesManager;

class Main_menu : public Scene {
private:
	sf::Text snakeTxt;
	sf::Text gameTxt;
	Button playBtn;
	Button helpBtn;
	Button quitBtn;
	Button leaderBtn;
	std::unique_ptr<Scene> scenePtr;
public:
	Main_menu();
	virtual void setScene(sf::RenderWindow& window);
	virtual void windowHandle(sf::RenderWindow& window);
};