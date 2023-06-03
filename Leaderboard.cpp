#include "Leaderboard.h"

void Leaderboard::show_leader(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	menuBtn.init("Go back to main menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 450 }, sf::Color(110, 120, 110), sf::Color::White);
	leaderboard.setString("Leaderboard");
	leaderboard.setCharacterSize(120);
	leaderboard.setFont(ResourcesMan::getFont("secondary"));
	leaderboard.setFillColor(sf::Color::Green);
	leaderboard.setPosition(xPos, yPos - 450.0f);
	leaderboard.setOrigin(leaderboard.getLocalBounds().left + leaderboard.getLocalBounds().width / 2.0f, leaderboard.getLocalBounds().top + leaderboard.getLocalBounds().height / 2.0f);
	nameLabel.setString("Player");
	nameLabel.setCharacterSize(80);
	nameLabel.setFont(ResourcesMan::getFont("secondary"));
	nameLabel.setFillColor(sf::Color::White);
	nameLabel.setPosition(xPos -  300.f, yPos - 300.0f);
	nameLabel.setOrigin(nameLabel.getLocalBounds().left + nameLabel.getLocalBounds().width / 2.0f, nameLabel.getLocalBounds().top + nameLabel.getLocalBounds().height / 2.0f);
	scoreLabel.setString("Score");
	scoreLabel.setCharacterSize(80);
	scoreLabel.setFont(ResourcesMan::getFont("secondary"));
	scoreLabel.setFillColor(sf::Color::White);
	scoreLabel.setPosition(xPos + 300.f, yPos - 300.0f);
	scoreLabel.setOrigin(scoreLabel.getLocalBounds().left + scoreLabel.getLocalBounds().width / 2.0f, scoreLabel.getLocalBounds().top + scoreLabel.getLocalBounds().height / 2.0f);
	playersNames.setCharacterSize(40);
	playersNames.setFont(ResourcesMan::getFont("secondary"));
	playersNames.setFillColor(sf::Color::White);
	playersNames.setPosition(xPos - 300.f, yPos + 350.0f);
	playersScores.setCharacterSize(40);
	playersScores.setFont(ResourcesMan::getFont("secondary"));
	playersScores.setFillColor(sf::Color::White);
	playersScores.setPosition(xPos + 300.f, yPos + 350.0f);
	top.setSize(sf::Vector2f(window.getSize().x, 350.f));
	top.setFillColor(sf::Color::Black);
	top.setPosition(0.f, 0.f);
	bottom.setSize(sf::Vector2f(window.getSize().x, 200.f));
	bottom.setFillColor(sf::Color::Black);
	bottom.setPosition(0.f, window.getSize().y - bottom.getSize().y);
	loadPlayerData();
	playersNames.setOrigin(playersNames.getLocalBounds().left + playersNames.getLocalBounds().width / 2.0f, yPos);
	playersScores.setOrigin(playersScores.getLocalBounds().left + playersScores.getLocalBounds().width / 2.0f, yPos);
	leader_option(window);
}

void Leaderboard::loadPlayerData() {
	std::ifstream inputFile("data/scores.txt");
	std::string line;
	int maxNameLength = 0;
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		PlayerData player;
		if (iss >> player.name >> player.score) {
			if (player.name.length() > maxNameLength) {
				maxNameLength = player.name.length();
			}
			players.push_back(player);
		}
	}
	inputFile.close();
	std::sort(players.begin(), players.end());
	std::string namesText;
	std::string scoresText;
	std::stringstream names_stream;
	std::stringstream scores_stream;
	for (const auto& player : players) {
		names_stream << std::setw(maxNameLength) << player.name << "\n";
		scores_stream << std::setw(5)<< player.score << "\n";
		namesText += names_stream.str();
		scoresText += scores_stream.str();
		names_stream.str("");
		scores_stream.str("");
	}
	playersNames.setString(namesText);
	playersScores.setString(scoresText);
}

void Leaderboard::leader_option(sf::RenderWindow& window) {
	float scrollSpeed = 15.f;
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseMoved:
				if (menuBtn.isMouseHover(window)) {
					menuBtn.setBtnColor(sf::Color(76, 78, 76));
				}
				else
					menuBtn.setBtnColor(sf::Color(110, 120, 110));
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (menuBtn.isMouseHover(window)) {
						Main_menu m;
						m.show_menu(window);
						break;
					}
				}
			case sf::Event::MouseWheelScrolled:
				if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (e.mouseWheelScroll.delta > 0)
					{
						playersNames.move(0.f, -scrollSpeed);
						playersScores.move(0.f, -scrollSpeed);
					}
					else if (e.mouseWheelScroll.delta < 0)
					{
						playersNames.move(0.f, scrollSpeed);
						playersScores.move(0.f, scrollSpeed);
					}
				}
			}

		}
		window.clear();
		window.draw(playersNames);
		window.draw(playersScores);
		window.draw(top);
		window.draw(bottom);
		window.draw(leaderboard);
		window.draw(nameLabel);
		window.draw(scoreLabel);
		menuBtn.drawTo(window);
		window.display();
	}
}