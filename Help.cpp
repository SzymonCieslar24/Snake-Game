#include "Help.h"

Help::Help() :
	howToTxt("How to play?", ResourcesMan::getFont("primary"), 120),
	helpTxt("This is the simple snake game. \nYou control snake with WASD or by using arrows on your keyboard. \nYour aim is to earn the highest score by eating fruits that appreas on the ground. \nAfter eating the fruit the snake grows depending on different fruit. \nThe game ends when snake hits the wall or his own body.", 
		ResourcesMan::getFont("secondary"), 40),
	quitBtn("Back to menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	scenePtr(nullptr)
{
	howToTxt.setFillColor(sf::Color::Green);
	howToTxt.setOrigin(howToTxt.getLocalBounds().left + howToTxt.getLocalBounds().width / 2.0f, howToTxt.getLocalBounds().top + howToTxt.getLocalBounds().height / 2.0f);
	helpTxt.setFillColor(sf::Color::White);
	helpTxt.setOrigin(helpTxt.getLocalBounds().left + helpTxt.getLocalBounds().width / 2.0f, helpTxt.getLocalBounds().top + helpTxt.getLocalBounds().height / 2.0f);
}

void Help::setScene(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	quitBtn.setBtnPosition({ xPos, yPos + 250.f });
	howToTxt.setPosition(xPos, yPos - 300.0f);
	helpTxt.setPosition(xPos, yPos - 50.0f);
	windowHandle(window);
}
void Help::windowHandle(sf::RenderWindow& window) {
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
						scenePtr = std::make_unique<Main_menu>();
						scenePtr->setScene(window);
						break;
					}
				}
			break;
			}
		}
		window.clear();
		window.draw(howToTxt);
		window.draw(helpTxt);
		quitBtn.drawTo(window);
		window.display();
	}
}