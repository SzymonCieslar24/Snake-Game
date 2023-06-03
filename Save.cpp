#include "Save.h"

void Save::show_save(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	menuBtn.init("Go back to main menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, { xPos, yPos + 300}, sf::Color(110, 120, 110), sf::Color::White);
	info.setString("Type your nickname in the textbox below.");
	info.setCharacterSize(50);
	info.setFont(ResourcesMan::getFont("secondary"));
	info.setFillColor(sf::Color::White);
	info.setPosition(xPos, yPos - 150.0f);
	info.setOrigin(info.getLocalBounds().left + info.getLocalBounds().width / 2.0f, info.getLocalBounds().top + info.getLocalBounds().height / 2.0f);
	input.setCharacterSize(80);
	input.setFont(ResourcesMan::getFont("primary"));
	input.setFillColor(sf::Color::White);
	input.setPosition(xPos, yPos);
	returnInfo.setString("Your nick should consist of letters and optionally numbers.");
	returnInfo.setCharacterSize(50);
	returnInfo.setFont(ResourcesMan::getFont("secondary"));
	returnInfo.setFillColor(sf::Color::White);
	returnInfo.setPosition(xPos, yPos + 150.0f);
	returnInfo.setOrigin(returnInfo.getLocalBounds().left + returnInfo.getLocalBounds().width / 2.0f, returnInfo.getLocalBounds().top + returnInfo.getLocalBounds().height / 2.0f);
	save_option(window);
}

void Save::savePlayerData(std::string& playerName, int& score) {
	std::filesystem::path dataDir = "data";
	if (!std::filesystem::exists(dataDir)) {
		std::filesystem::create_directory(dataDir);
	}
	std::filesystem::path filePath = dataDir / ("scores.txt");
	std::ofstream outputFile(filePath, std::ios::app);
	if (outputFile.is_open()) {
		outputFile << playerName << " " << score << std::endl;
		outputFile.close();
	}
	else {
		std::cout << "Failed to open the file for writing." << std::endl;
	}
}

void Save::save_option(sf::RenderWindow& window) {
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
						Main_menu m;
						m.show_menu(window);
						break;
					}
				}
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
						std::regex pattern ("^[A-Za-z]+[A-Za-z0-9]*$");
						if (std::regex_match(inputStr, pattern)) {
							savePlayerData(inputStr, Game::getScore());
							Main_menu m;
							m.show_menu(window);
							break;
						}
						else {
							returnInfo.setString("Invalid nickname! Only letters and numbers are allowed!");
							returnInfo.setFillColor(sf::Color::Red);
							returnInfo.setOrigin(returnInfo.getLocalBounds().left + returnInfo.getLocalBounds().width / 2.0f, returnInfo.getLocalBounds().top + returnInfo.getLocalBounds().height / 2.0f);
						}
					}
					else
					{
						inputStr += static_cast<char>(e.text.unicode);
					}
					input.setString(inputStr);
					input.setOrigin(input.getLocalBounds().left + input.getLocalBounds().width / 2.0f, input.getLocalBounds().top + input.getLocalBounds().height / 2.0f);
				}
			}
		}
	window.clear();
	window.draw(info);
	window.draw(input);
	window.draw(returnInfo);
	menuBtn.drawTo(window);
	window.display();
	}
}