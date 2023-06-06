#include "MainMenu.h"

Main_menu::Main_menu() :
	snakeTxt("SNAKE", ResourcesMan::getFont("primary"), 180),
	gameTxt("THE GAME", ResourcesMan::getFont("primary"), 120),
	playBtn("Play", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	leaderBtn("Leaderboard", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	helpBtn("Help", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	quitBtn("Exit", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	scenePtr(nullptr)
{
	snakeTxt.setFillColor(sf::Color::Green);
	snakeTxt.setOrigin(snakeTxt.getLocalBounds().left + snakeTxt.getLocalBounds().width / 2.0f, snakeTxt.getLocalBounds().top + snakeTxt.getLocalBounds().height / 2.0f);
	gameTxt.setFillColor(sf::Color::White);
	gameTxt.setOrigin(gameTxt.getLocalBounds().left + gameTxt.getLocalBounds().width / 2.0f, gameTxt.getLocalBounds().top + gameTxt.getLocalBounds().height / 2.0f);
}

void Main_menu::setScene(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	playBtn.setBtnPosition({ xPos,yPos });
	leaderBtn.setBtnPosition({ xPos,yPos + 140.f });
	helpBtn.setBtnPosition({ xPos,yPos + 280.f});
	quitBtn.setBtnPosition({ xPos,yPos + 420.f});
	snakeTxt.setPosition(xPos, yPos - 300.0f);
	gameTxt.setPosition(xPos, yPos - 150.0f);
	windowHandle(window);
}
void Main_menu::windowHandle(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseMoved:
				if (playBtn.isMouseHover(window)) {
					playBtn.setBtnColor(sf::Color(20, 150, 20));
				}
				else
					playBtn.setBtnColor(sf::Color(110, 120, 110));
				if (leaderBtn.isMouseHover(window)) {
					leaderBtn.setBtnColor(sf::Color(20, 150, 20));
				}
				else
					leaderBtn.setBtnColor(sf::Color(110, 120, 110));
				if (helpBtn.isMouseHover(window)) {
					helpBtn.setBtnColor(sf::Color(20, 150, 20));
				}
				else
					helpBtn.setBtnColor(sf::Color(110, 120, 110));
				if (quitBtn.isMouseHover(window)) {
					quitBtn.setBtnColor(sf::Color(20, 150, 20));
				}
				else
					quitBtn.setBtnColor(sf::Color(110, 120, 110));
				break;
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (playBtn.isMouseHover(window)) {
						scenePtr = std::make_unique<Game>();
						scenePtr -> setScene(window);
						break;
					}
					if (leaderBtn.isMouseHover(window)) {
						scenePtr = std::make_unique<Leaderboard>();
						scenePtr -> setScene(window);
						break;
					}
					else if (helpBtn.isMouseHover(window)) {
						scenePtr = std::make_unique<Help>();
						scenePtr -> setScene(window);
						break;
					}
					else if (quitBtn.isMouseHover(window)) {
						window.close();
						break;
					}
				}
			break;
			}
		}
		window.clear();
		window.draw(snakeTxt);
		window.draw(gameTxt);
		playBtn.drawTo(window);
		leaderBtn.drawTo(window);
		helpBtn.drawTo(window);
		quitBtn.drawTo(window);
		window.display();
	}
}