#include "Save.h"

void Save::show_save(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	info.setString("Type your nickname in the textbox below.");
	info.setCharacterSize(50);
	info.setFont(ResourcesMan::getFont("secondary"));
	info.setFillColor(sf::Color::White);
	info.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 150.0f);
	info.setOrigin(info.getLocalBounds().left + info.getLocalBounds().width / 2.0f, info.getLocalBounds().top + info.getLocalBounds().height / 2.0f);
	input.setCharacterSize(80);
	input.setFont(ResourcesMan::getFont("secondary"));
	input.setFillColor(sf::Color::White);
	input.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	error.setString("Invalid nickname");
	error.setCharacterSize(50);
	error.setFont(ResourcesMan::getFont("secondary"));
	error.setFillColor(sf::Color::Red);
	error.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + 150.0f);
	error.setOrigin(error.getLocalBounds().left + error.getLocalBounds().width / 2.0f, error.getLocalBounds().top + error.getLocalBounds().height / 2.0f);
	save_option(window);
}
void Save::save_option(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				if (e.text.unicode < 128)
				{
					if (e.text.unicode == 8) // Backspace
					{
						if (!inputStr.empty())
						{
							inputStr.pop_back();
						}
					}
					else if (e.text.unicode == 13) // Enter
					{
						// Tutaj mo¿na wykonaæ jakieœ dzia³anie po wciœniêciu Enter
						pattern = ("^[A-Za-z]+[A-Za-z0-9]*$");
						//if () {
							// Wprowadzony tekst jest poprawny
							// Mo¿esz podj¹æ odpowiednie dzia³ania
						//}
						//else {
							// Wprowadzony tekst jest niepoprawny
							// Wyœwietl komunikat b³êdu lub wykonaj inne czynnoœci
						//}
					}
					else
					{
						inputStr += static_cast<char>(e.text.unicode);
					}
					input.setString(inputStr);
				}
			}
		}
	window.clear();
	window.draw(info);
	window.draw(input);
	input.setOrigin(input.getLocalBounds().left + input.getLocalBounds().width / 2.0f, input.getLocalBounds().top + input.getLocalBounds().height / 2.0f);
	//window.draw(error);
	window.display();
	}
}