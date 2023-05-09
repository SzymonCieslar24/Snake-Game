#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RectangleShape btn;
	sf::Text txt;
public:
	Button(){}
	void init(std::string t, sf::Font &f, int txt_size, sf::Vector2f size, sf::Vector2f pos, sf::Color btnColor, sf::Color txtColor) {
		txt.setString(t);
		txt.setFillColor(txtColor);
		txt.setFont(f);
		txt.setCharacterSize(txt_size);
		txt.setPosition(pos);
		txt.setOrigin(txt.getLocalBounds().left + txt.getLocalBounds().width / 2.f, txt.getLocalBounds().top + txt.getLocalBounds().height / 2.f);
		btn.setSize(size);
		btn.setFillColor(btnColor);
		btn.setPosition(pos);
		btn.setOrigin(btn.getLocalBounds().left + btn.getLocalBounds().width / 2.f, btn.getLocalBounds().top + btn.getLocalBounds().height / 2.f);
	}
	void setBtnColor(sf::Color c) {
		btn.setFillColor(c);
	}
	void drawTo(sf::RenderWindow& window) {
		window.draw(btn);
		window.draw(txt);
	}
	bool isMouseHover(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		float btnLeftX = btn.getPosition().x - btn.getOrigin().x;
		float btnUpY = btn.getPosition().y - btn.getOrigin().y;
		float btnRightX = btn.getPosition().x + btn.getLocalBounds().width - btn.getOrigin().x;
		float btnDownY = btn.getPosition().y + btn.getLocalBounds().height - btn.getOrigin().y;
		if (mouseX < btnRightX && mouseX > btnLeftX && mouseY < btnDownY && mouseY > btnUpY) {
			return true;
		}
		return false;
	}
};