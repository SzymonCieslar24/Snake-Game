#include "GameOver.h"

GameOver::GameOver():
	overTxt("GAME OVER", ResourcesMan::getFont("primary"),180),
	scoreTxt("Your score: " + std::to_string(Game::getScore()), ResourcesMan::getFont("primary"), 100),
	playAgainBtn("Play Again", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	saveScoreBtn("Save score", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	menuBtn("Go to main menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	scenePtr(nullptr)
{
	overTxt.setFillColor(sf::Color::Red);
	overTxt.setOrigin(overTxt.getLocalBounds().left + overTxt.getLocalBounds().width / 2.0f, overTxt.getLocalBounds().top + overTxt.getLocalBounds().height / 2.0f);
	scoreTxt.setFillColor(sf::Color::White);
	scoreTxt.setOrigin(scoreTxt.getLocalBounds().left + scoreTxt.getLocalBounds().width / 2.0f, scoreTxt.getLocalBounds().top + scoreTxt.getLocalBounds().height / 2.0f);
}

void GameOver::setScene(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	playAgainBtn.setBtnPosition({ xPos, yPos });
	saveScoreBtn.setBtnPosition({ xPos, yPos +140.f});
	menuBtn.setBtnPosition({ xPos, yPos +280.f});
	overTxt.setPosition(xPos, yPos - 300.0f);
	scoreTxt.setPosition(xPos, yPos - 150.0f);
	windowHandle(window);
}
void GameOver::windowHandle(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseMoved:
				if (playAgainBtn.isMouseHover(window)) {
					playAgainBtn.setBtnColor(sf::Color(76, 78, 76));
				}
				else
					playAgainBtn.setBtnColor(sf::Color(110, 120, 110));
				if (saveScoreBtn.isMouseHover(window)) {
					saveScoreBtn.setBtnColor(sf::Color(76, 78, 76));
				}
				else
					saveScoreBtn.setBtnColor(sf::Color(110, 120, 110));
				if (menuBtn.isMouseHover(window)) {
					menuBtn.setBtnColor(sf::Color(76, 78, 76));
				}
				else
					menuBtn.setBtnColor(sf::Color(110, 120, 110));
				break;
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (playAgainBtn.isMouseHover(window)) {
						scenePtr = std::make_unique<Game>();
						scenePtr->setScene(window);
						break;
					}
					else if (saveScoreBtn.isMouseHover(window)) {
						scenePtr = std::make_unique<Save>();
						scenePtr->setScene(window);
					}
					else if (menuBtn.isMouseHover(window)) {
						scenePtr = std::make_unique<Main_menu>();
						scenePtr->setScene(window);
						break;
					}
				}
				break;
			}
		}
		window.clear();
		window.draw(overTxt);
		window.draw(scoreTxt);
		playAgainBtn.drawTo(window);
		saveScoreBtn.drawTo(window);
		menuBtn.drawTo(window);
		window.display();
	}
}

