#include "GameOver.h"

void GameOver::show_gameOver(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	playAgainBtn.init("Play Again", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos}, sf::Color(110, 120, 110), sf::Color::White);
	saveScoreBtn.init("Save score", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 140.f }, sf::Color(110, 120, 110), sf::Color::White);
	menuBtn.init("Go to main menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 280.f }, sf::Color(110, 120, 110), sf::Color::White);
	txt1.setString("GAME OVER");
	txt1.setCharacterSize(180);
	txt1.setFont(ResourcesMan::getFont("primary"));
	txt1.setFillColor(sf::Color::Red);
	txt1.setPosition(xPos, yPos - 300.0f);
	txt1.setOrigin(txt1.getLocalBounds().left + txt1.getLocalBounds().width / 2.0f, txt1.getLocalBounds().top + txt1.getLocalBounds().height / 2.0f);
	txt2.setString("Your score: " + std::to_string(Game::getScore()));
	txt2.setCharacterSize(100);
	txt2.setFont(ResourcesMan::getFont("primary"));
	txt2.setFillColor(sf::Color::White);
	txt2.setPosition(xPos, yPos - 150.0f);
	txt2.setOrigin(txt2.getLocalBounds().left + txt2.getLocalBounds().width / 2.0f, txt2.getLocalBounds().top + txt2.getLocalBounds().height / 2.0f);
	gameOver_option(window);
}
void GameOver::gameOver_option(sf::RenderWindow& window) {
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
						Game g;
						g.initMap(window);
						break;
					}
					else if (saveScoreBtn.isMouseHover(window)) {
						Save s;
						s.show_save(window);
					}
					else if (menuBtn.isMouseHover(window)) {
						Main_menu m;
						m.show_menu(window);
						break;
					}
				}
				break;
			}
		}
		window.clear();
		window.draw(txt1);
		window.draw(txt2);
		playAgainBtn.drawTo(window);
		saveScoreBtn.drawTo(window);
		menuBtn.drawTo(window);
		window.display();
	}
}

