#ifndef VIGBUTTON_H
#define VIGBUTTON_H

#include <memory>
#include <functional>
#include "Button.h"
#include "BattleGraphics.h"

class VoidIntGButton : public Button {
public:
	//what the button does
	std::function<void(std::shared_ptr<BattleGraphics>, int)> action;
	std::shared_ptr<BattleGraphics> battleG;
	int pass;

	VoidIntGButton() {}

	VoidIntGButton(int xP, int yP, int xL, int yL, const std::shared_ptr<sf::RenderWindow> &win, const std::shared_ptr<BattleGraphics> &b) {
		pos = sf::Vector2f(xP, yP);
		size = sf::Vector2f(xL, yL);
		window = win;
		battleG = b;
	}

	void runFunction() override {
		action(battleG, pass);
	}
};

#endif