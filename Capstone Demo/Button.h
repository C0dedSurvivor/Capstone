#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
	//size and position of the "button"
	sf::Vector2f pos;
	sf::Vector2f size;

	bool enabled = true;

	std::shared_ptr<sf::RenderWindow> window;

	Button() {

	}

	Button(int xP, int yP, int xL, int yL, const std::shared_ptr<sf::RenderWindow> &win) : window(win) {
		pos = sf::Vector2f(xP, yP);
		size = sf::Vector2f(xL, yL);
	}

	bool checkButton() {
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);
		if (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y) {
			return true;
		}
		return false;
	}

	virtual void runFunction() {}

	void switchEnabled() {
		enabled = !enabled;
	}

	void setPosition(int x, int y) {
		pos = sf::Vector2f(x, y);
	}
};

#endif