#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"

import Button;
import ResourcesManager;

class Help : public Scene{
private:
	sf::Text howToTxt;
	sf::Text helpTxt;
	Button quitBtn;
	std::unique_ptr<Scene> scenePtr;
public:
	Help();
	virtual void setScene(sf::RenderWindow& window);
	virtual void windowHandle(sf::RenderWindow& window);
};
