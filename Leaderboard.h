#pragma once

#include <iostream>
#include <regex>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MainMenu.h"
#include "Game.h"
#include "ResourcesManager.h"

class Leaderboard {
private:
	sf::Text leaderboard;
	sf::Text nameLabel;
	sf::Text scoreLabel;
	sf::Text playersNames;
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::Text playersScores;
	Button menuBtn;
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
	void show_leader(sf::RenderWindow& window);
	void loadPlayerData();
	void leader_option(sf::RenderWindow& window);
};
