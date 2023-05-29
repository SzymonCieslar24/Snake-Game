#pragma once

#include <iostream>
#include <regex>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"

class Save {
private:
	sf::Text info;
	sf::Text input;
	sf::Text error;
	std::string inputStr;
	std::regex pattern;
public:
	void show_save(sf::RenderWindow& window);
	void save_option(sf::RenderWindow& window);
};
