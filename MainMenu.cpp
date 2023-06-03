#include "MainMenu.h"

void Main_menu::show_menu(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	playBtn.init("Play", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos }, sf::Color(110, 120, 110), sf::Color::White);
	leaderBtn.init("Leaderboard", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 140.f }, sf::Color(110, 120, 110), sf::Color::White);
	helpBtn.init("Help", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 280.f }, sf::Color(110, 120, 110), sf::Color::White);
	quitBtn.init("Exit", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 420.f }, sf::Color(110, 120, 110), sf::Color::White);
	txt1.setString("SNAKE");
	txt1.setCharacterSize(180);
	txt1.setFont(ResourcesMan::getFont("primary"));
	txt1.setFillColor(sf::Color::Green);
	txt1.setPosition(xPos, yPos - 300.0f);
	txt1.setOrigin(txt1.getLocalBounds().left + txt1.getLocalBounds().width / 2.0f, txt1.getLocalBounds().top + txt1.getLocalBounds().height / 2.0f);
	txt2.setString("THE GAME");
	txt2.setCharacterSize(120);
	txt2.setFont(ResourcesMan::getFont("primary"));
	txt2.setFillColor(sf::Color::White);
	txt2.setPosition(xPos, yPos - 150.0f);
	txt2.setOrigin(txt2.getLocalBounds().left + txt2.getLocalBounds().width / 2.0f, txt2.getLocalBounds().top + txt2.getLocalBounds().height / 2.0f);
	menu_option(window);
}
void Main_menu::menu_option(sf::RenderWindow& window) {
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
						Game g;
						g.initMap(window);
						break;
					}
					if (leaderBtn.isMouseHover(window)) {
						Leaderboard l;
						l.show_leader(window);
						break;
					}
					else if (helpBtn.isMouseHover(window)) {
						Help h;
						h.show_help(window);
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
		window.draw(txt1);
		window.draw(txt2);
		playBtn.drawTo(window);
		leaderBtn.drawTo(window);
		helpBtn.drawTo(window);
		quitBtn.drawTo(window);
		window.display();
	}
}