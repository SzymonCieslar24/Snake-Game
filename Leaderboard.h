#pragma once

#include <iostream>
#include <memory>
#include <regex>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>
#include <ranges>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MainMenu.h"
#include "Game.h"

import Button;
import ResourcesManager;

class Leaderboard : public Scene{
private:
	sf::Text leaderTxt;
	sf::Text nameLabelTxt;
	sf::Text scoreLabelTxt;
	sf::Text playersNamesTxt;
	sf::Text playersScoresTxt;
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	Button menuBtn;
	std::unique_ptr<Scene> scenePtr;
	struct PlayerData {
		std::string name;
		int score;
		bool operator<(const PlayerData& other) const {
			if (score == other.score) {
				return name < other.name;
			}
			else {
				return score > other.score;
			}
		}
	};
	std::vector<PlayerData> players;
public:
	Leaderboard();
	virtual void setScene(sf::RenderWindow& window);
	void loadPlayerData();
	virtual void windowHandle(sf::RenderWindow& window);
};
