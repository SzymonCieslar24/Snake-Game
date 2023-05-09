#include "MainMenu.h"
#include "Help.h"
#include "Game.h"

void Main_menu::show_menu(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	playBtn.init("Play", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos }, sf::Color::Green, sf::Color::White);
	helpBtn.init("Help", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 140.f }, sf::Color::Green, sf::Color::White);
	quitBtn.init("Exit", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 280.f }, sf::Color::Green, sf::Color::White);
	txt1.setString("SNAKE");
	txt1.setCharacterSize(180);
	txt1.setFont(ResourcesMan::getFont("primary"));
	txt1.setFillColor(sf::Color::Green);
	txt1.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 300.0f);
	txt1.setOrigin(txt1.getLocalBounds().left + txt1.getLocalBounds().width / 2.0f, txt1.getLocalBounds().top + txt1.getLocalBounds().height / 2.0f);
	txt2.setString("THE GAME");
	txt2.setCharacterSize(120);
	txt2.setFont(ResourcesMan::getFont("primary"));
	txt2.setFillColor(sf::Color::Green);
	txt2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 150.0f);
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
					playBtn.setBtnColor(sf::Color::Red);
				}
				else
					playBtn.setBtnColor(sf::Color::Green);
				if (helpBtn.isMouseHover(window)) {
					helpBtn.setBtnColor(sf::Color::Red);
				}
				else
					helpBtn.setBtnColor(sf::Color::Green);
				if (quitBtn.isMouseHover(window)) {
					quitBtn.setBtnColor(sf::Color::Red);
				}
				else
					quitBtn.setBtnColor(sf::Color::Green);
				break;
			case sf::Event::MouseButtonPressed:
				if (playBtn.isMouseHover(window)) {
					Game g;
					g.initMap(window);
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
				break;
			}
		}
		window.clear();
		window.draw(txt1);
		window.draw(txt2);
		playBtn.drawTo(window);
		helpBtn.drawTo(window);
		quitBtn.drawTo(window);
		window.display();
	}
}

//int main() {
//	//Main_menu menu;
//	//menu.show_menu();
//	Game game;
//	game.runGame();
//	return 0;
//}