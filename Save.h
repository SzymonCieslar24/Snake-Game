#pragma once

#include <iostream>
#include <regex>
#include <filesystem>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MainMenu.h"
#include "Game.h"
#include "ResourcesManager.h"

class Save {
private:
	sf::Text info;
	sf::Text input;
	sf::Text returnInfo;
	Button menuBtn;
	std::string inputStr;
public:
	void show_save(sf::RenderWindow& window);
	void savePlayerData(std::string& playerName, int& score);
	void save_option(sf::RenderWindow& window);
};
