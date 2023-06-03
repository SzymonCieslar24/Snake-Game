#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Help.h"
#include "Game.h"
#include "Leaderboard.h"
#include "ResourcesManager.h"

class Main_menu {
private:
	sf::Text txt1;
	sf::Text txt2;
	Button playBtn;
	Button helpBtn;
	Button quitBtn;
	Button leaderBtn;
public:
	void show_menu(sf::RenderWindow& window);
	void menu_option(sf::RenderWindow& window);
};