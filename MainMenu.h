#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ResourcesManager.h"

class Main_menu {
private:
	sf::Text txt1;
	sf::Text txt2;
	Button playBtn;
	Button helpBtn;
	Button quitBtn;
public:
	void show_menu(sf::RenderWindow& window);
	void menu_option(sf::RenderWindow& window);
};