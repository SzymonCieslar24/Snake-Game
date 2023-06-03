#include "Help.h"
#include "MainMenu.h"

void Help::show_help(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	quitBtn.init("Back to menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 250.f }, sf::Color(110, 120, 110), sf::Color::White);
	txt1.setString("How to play?");
	txt1.setCharacterSize(120);
	txt1.setFont(ResourcesMan::getFont("primary"));
	txt1.setFillColor(sf::Color::Green);
	txt1.setPosition(xPos, yPos - 300.0f);
	txt1.setOrigin(txt1.getLocalBounds().left + txt1.getLocalBounds().width / 2.0f, txt1.getLocalBounds().top + txt1.getLocalBounds().height / 2.0f);
	txt2.setString("This is the simple snake game. \nYou control snake with WASD or by using arrows on your keyboard. \nYour aim is to earn the highest score by eating fruits that appreas on the ground. \nAfter eating the fruit the snake grows depending on different fruit. \nThe game ends when snake hits the wall or his own body.");
	txt2.setCharacterSize(40);
	txt2.setFont(ResourcesMan::getFont("secondary"));
	txt2.setFillColor(sf::Color::White);
	txt2.setPosition(xPos, yPos - 50.0f);
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
					quitBtn.setBtnColor(sf::Color(20, 150, 20));
				}
				else
					quitBtn.setBtnColor(sf::Color(110, 120, 110));
				break;
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (quitBtn.isMouseHover(window)) {
						Main_menu menu;
						menu.show_menu(window);
						break;
					}
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