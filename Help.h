#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "Button.h"

class Help {
private:
	sf::Text txt1;
	sf::Text txt2;
	Button quitBtn;

public:
	void show_help(sf::RenderWindow& window);
	void help_option(sf::RenderWindow& window);
};
