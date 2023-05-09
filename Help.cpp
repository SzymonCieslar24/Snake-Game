#include "Help.h"
#include "MainMenu.h"

void Help::show_help(sf::RenderWindow& window) {
	font.loadFromFile("fonts/Pacifico-Regular.ttf");
	font2.loadFromFile("fonts/Arial.ttf");
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	quitBtn.init("Back to menu", font, 60, { 800, 100 }, { xPos, yPos + 250.f }, sf::Color::Green, sf::Color::White);
	txt1.setString("How to play?");
	txt1.setCharacterSize(120);
	txt1.setFont(font);
	txt1.setFillColor(sf::Color::Green);
	txt1.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 300.0f);
	txt1.setOrigin(txt1.getLocalBounds().left + txt1.getLocalBounds().width / 2.0f, txt1.getLocalBounds().top + txt1.getLocalBounds().height / 2.0f);
	txt2.setString("This is the simple snake game. \nYou control snake with WASD or by using arrows on your keyboard. \nYour aim is to earn the highest score by eating fruits that appreas on the ground. \nAfter eating the fruit the snake grows depending on different fruit. \nThe game ends when snake hits the wall or his own body.");
	txt2.setCharacterSize(40);
	txt2.setFont(font2);
	txt2.setFillColor(sf::Color::White);
	txt2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 50.0f);
	txt2.setOrigin(txt2.getLocalBounds().left + txt2.getLocalBounds().width / 2.0f, txt2.getLocalBounds().top + txt2.getLocalBounds().height / 2.0f);
	help_option(window);
}
void Help::help_option(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseMoved:
				if (quitBtn.isMouseHover(window)) {
					quitBtn.setBtnColor(sf::Color::Red);
				}
				else
					quitBtn.setBtnColor(sf::Color::Green);
				break;
			case sf::Event::MouseButtonPressed:
				if (quitBtn.isMouseHover(window)) {
					Main_menu menu;
					menu.show_menu(window);
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(txt1);
		window.draw(txt2);
		quitBtn.drawTo(window);
		window.display();
	}
}