#ifndef VIBUTTON_H
#define VIBUTTON_H

#include <functional>
#include "Button.h"

class VoidIntButton : public Button{
public:
	//what the button does
	std::function<void(std::shared_ptr<Battle>, int)> action;
	std::shared_ptr<Battle> battle;
	int pass;

	VoidIntButton(){}

	VoidIntButton(int xP, int yP, int xL, int yL, const std::shared_ptr<sf::RenderWindow> &win, const std::shared_ptr<Battle> &b) {
		pos = sf::Vector2f(xP, yP);
		size = sf::Vector2f(xL, yL);
		window = win;
		battle = b;
	}

	void runFunction() override {
		action(battle, pass);
	}
};

#endif