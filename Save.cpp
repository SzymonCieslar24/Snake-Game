#include "Save.h"

Save::Save():
	saveTxt("Type your nickname in the textbox below.", ResourcesMan::getFont("secondary"),50),
	inputTxt("", ResourcesMan::getFont("primary"),80),
	returnInfoTxt("Your nick should consist of letters and optionally numbers.", ResourcesMan::getFont("secondary"),50),
	menuBtn("Go back to main menu", ResourcesMan::getFont("primary"), 60, { 800, 100 }, sf::Color(110, 120, 110), sf::Color::White),
	scenePtr(nullptr)
{
	saveTxt.setFillColor(sf::Color::White);
	saveTxt.setOrigin(saveTxt.getLocalBounds().left + saveTxt.getLocalBounds().width / 2.0f, saveTxt.getLocalBounds().top + saveTxt.getLocalBounds().height / 2.0f);
	inputTxt.setFillColor(sf::Color::White);
	returnInfoTxt.setFillColor(sf::Color::White);
	returnInfoTxt.setOrigin(returnInfoTxt.getLocalBounds().left + returnInfoTxt.getLocalBounds().width / 2.0f, returnInfoTxt.getLocalBounds().top + returnInfoTxt.getLocalBounds().height / 2.0f);
}

void Save::setScene(sf::RenderWindow& window) {
	float xPos = window.getSize().x / 2.f;
	float yPos = window.getSize().y / 2.f;
	menuBtn.setBtnPosition({ xPos, yPos + 300});
	saveTxt.setPosition(xPos, yPos - 150.0f);
	inputTxt.setPosition(xPos, yPos);
	returnInfoTxt.setPosition(xPos, yPos + 150.0f);
	windowHandle(window);
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

void Save::windowHandle(sf::RenderWindow& window) {
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
						scenePtr = std::make_unique<Main_menu>();
						scenePtr->setScene(window);
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
							scenePtr = std::make_unique<Main_menu>();
							scenePtr->setScene(window);
							break;
						}
						else {
							returnInfoTxt.setString("Invalid nickname! Only letters and numbers are allowed!");
							returnInfoTxt.setFillColor(sf::Color::Red);
							returnInfoTxt.setOrigin(returnInfoTxt.getLocalBounds().left + returnInfoTxt.getLocalBounds().width / 2.0f, returnInfoTxt.getLocalBounds().top + returnInfoTxt.getLocalBounds().height / 2.0f);
						}
					}
					else
					{
						inputStr += static_cast<char>(e.text.unicode);
					}
					inputTxt.setString(inputStr);
					inputTxt.setOrigin(inputTxt.getLocalBounds().left + inputTxt.getLocalBounds().width / 2.0f, inputTxt.getLocalBounds().top + inputTxt.getLocalBounds().height / 2.0f);
				}
			}
		}
	window.clear();
	window.draw(saveTxt);
	window.draw(inputTxt);
	window.draw(returnInfoTxt);
	menuBtn.drawTo(window);
	window.display();
	}
}