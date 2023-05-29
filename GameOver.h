#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MainMenu.h"
#include "Game.h"
#include "Save.h"

class GameOver {
private:
	sf::Text txt1;
	sf::Text txt2;
	Button playAgainBtn;
	Button saveScoreBtn;
	Button menuBtn;
public:
	void show_gameOver(sf::RenderWindow& window);
	void gameOver_option(sf::RenderWindow& window);
};