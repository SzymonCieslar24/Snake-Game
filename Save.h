#pragma once

#include <iostream>
#include <memory>
#include <regex>
#include <filesystem>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"
#include "Game.h"

import Button;
import ResourcesManager;

class Save : public Scene{
private:
	sf::Text saveTxt;
	sf::Text inputTxt;
	sf::Text returnInfoTxt;
	Button menuBtn;
	std::string inputStr;
	std::unique_ptr<Scene> scenePtr;
public:
	Save();
	virtual void setScene(sf::RenderWindow& window);
	void savePlayerData(std::string& playerName, int& score);
	virtual void windowHandle(sf::RenderWindow& window);
};
