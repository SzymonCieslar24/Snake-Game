#pragma once

#include <SFML/Graphics.hpp>

class Scene {
public:
	virtual void setScene(sf::RenderWindow& window) = 0;
	virtual void windowHandle(sf::RenderWindow& window) = 0;
};
