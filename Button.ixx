export module Button;

import <iostream>;
import <SFML/Graphics.hpp>;

export class Button {
private:
	sf::RectangleShape btn;
	sf::Text txt;
public:
	Button();
	Button(std::string t, sf::Font& f, int txt_size, sf::Vector2f size, sf::Color btnColor, sf::Color txtColor);
	void setBtnPosition(sf::Vector2f pos);
	void setBtnColor(sf::Color c);
	void drawTo(sf::RenderWindow& window);
	bool isMouseHover(sf::RenderWindow& window);
};

Button::Button() {}

Button::Button(std::string t, sf::Font& f, int txt_size, sf::Vector2f size, sf::Color btnColor, sf::Color txtColor) :
	txt(t, f, txt_size),
	btn(size)
{
	txt.setFillColor(txtColor);
	txt.setOrigin(txt.getLocalBounds().left + txt.getLocalBounds().width / 2.f, txt.getLocalBounds().top + txt.getLocalBounds().height / 2.f);
	btn.setFillColor(btnColor);
	btn.setOrigin(btn.getLocalBounds().left + btn.getLocalBounds().width / 2.f, btn.getLocalBounds().top + btn.getLocalBounds().height / 2.f);
}

void Button::setBtnPosition(sf::Vector2f pos) {
	txt.setPosition(pos);
	btn.setPosition(pos);
}

void Button::setBtnColor(sf::Color c) {
	btn.setFillColor(c);
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(btn);
	window.draw(txt);
}
bool Button::isMouseHover(sf::RenderWindow& window) {
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