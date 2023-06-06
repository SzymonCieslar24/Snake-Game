#include "Leaderboard.h"

Leaderboard::Leaderboard():
	leaderTxt("Leaderboard", ResourcesMan::getFont("primary"), 120),
	nameLabelTxt("Player", ResourcesMan::getFont("primary"), 80),
	scoreLabelTxt("Score", ResourcesMan::getFont("primary"), 80),
	playersNamesTxt("", ResourcesMan::getFont("secondary"), 40),
	playersScoresTxt("", ResourcesMan::getFont("secondary"), 40),
	menuBtn("Go back to main menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	scenePtr(nullptr)
{
	leaderTxt.setFillColor(sf::Color::Green);
	leaderTxt.setOrigin(leaderTxt.getLocalBounds().left + leaderTxt.getLocalBounds().width / 2.0f, leaderTxt.getLocalBounds().top + leaderTxt.getLocalBounds().height / 2.0f);
	nameLabelTxt.setFillColor(sf::Color::White);
	nameLabelTxt.setOrigin(nameLabelTxt.getLocalBounds().left + nameLabelTxt.getLocalBounds().width / 2.0f, nameLabelTxt.getLocalBounds().top + nameLabelTxt.getLocalBounds().height / 2.0f);
	scoreLabelTxt.setFillColor(sf::Color::White);
	scoreLabelTxt.setOrigin(scoreLabelTxt.getLocalBounds().left + scoreLabelTxt.getLocalBounds().width / 2.0f, scoreLabelTxt.getLocalBounds().top + scoreLabelTxt.getLocalBounds().height / 2.0f);
	playersNamesTxt.setFillColor(sf::Color::White);
	playersScoresTxt.setFillColor(sf::Color::White);
	top.setFillColor(sf::Color::Black);
	bottom.setFillColor(sf::Color::Black);
}

void Leaderboard::setScene(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	menuBtn.setBtnPosition({ xPos, yPos + 450 });
	leaderTxt.setPosition(xPos, yPos - 450.0f);
	nameLabelTxt.setPosition(xPos -  300.f, yPos - 300.0f);
	scoreLabelTxt.setPosition(xPos + 300.f, yPos - 300.0f);
	playersNamesTxt.setPosition(xPos - 300.f, yPos + 350.0f);
	playersScoresTxt.setPosition(xPos + 300.f, yPos + 350.0f);
	top.setSize(sf::Vector2f(window.getSize().x, 350.f));
	top.setPosition(0.f, 0.f);
	bottom.setSize(sf::Vector2f(window.getSize().x, 200.f));
	bottom.setPosition(0.f, window.getSize().y - bottom.getSize().y);
	loadPlayerData();
	playersNamesTxt.setOrigin(playersNamesTxt.getLocalBounds().left + playersNamesTxt.getLocalBounds().width / 2.0f, yPos);
	playersScoresTxt.setOrigin(playersScoresTxt.getLocalBounds().left + playersScoresTxt.getLocalBounds().width / 2.0f, yPos);
	windowHandle(window);
}

void Leaderboard::loadPlayerData() {
	if (std::filesystem::exists("data/scores.txt")) {
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
			scores_stream << std::setw(5) << player.score << "\n";
			namesText += names_stream.str();
			scoresText += scores_stream.str();
			names_stream.str("");
			scores_stream.str("");
		}
		playersNamesTxt.setString(namesText);
		playersScoresTxt.setString(scoresText);
	}
	else {
		std::cout << "Can not find score file!" << std::endl;
	}
}

void Leaderboard::windowHandle(sf::RenderWindow& window) {
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
						scenePtr = std::make_unique<Main_menu>();
						scenePtr ->setScene(window);
						break;
					}
				}
			case sf::Event::MouseWheelScrolled:
				if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (e.mouseWheelScroll.delta > 0)
					{
						playersNamesTxt.move(0.f, -scrollSpeed);
						playersScoresTxt.move(0.f, -scrollSpeed);
					}
					else if (e.mouseWheelScroll.delta < 0)
					{
						playersNamesTxt.move(0.f, scrollSpeed);
						playersScoresTxt.move(0.f, scrollSpeed);
					}
				}
			}

		}
		window.clear();
		window.draw(playersNamesTxt);
		window.draw(playersScoresTxt);
		window.draw(top);
		window.draw(bottom);
		window.draw(leaderTxt);
		window.draw(nameLabelTxt);
		window.draw(scoreLabelTxt);
		menuBtn.drawTo(window);
		window.display();
	}
}