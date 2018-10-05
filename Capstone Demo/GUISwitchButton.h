#ifndef GSBUTTON_H
#define GSBUTTON_H

#include <functional>
#include <memory>
#include "Renderer.h"
#include "Button.h"

class GUISwitchButton : public Button {
public:
	//what the button does
	std::function<void(std::shared_ptr<Renderer>, int)> action;
	std::shared_ptr<Renderer> render;
	int pass;

	GUISwitchButton() {}

	GUISwitchButton(int xP, int yP, int xL, int yL, const std::shared_ptr<sf::RenderWindow> &win, const std::shared_ptr<Renderer> &r) {
		pos = sf::Vector2f(xP, yP);
		size = sf::Vector2f(xL, yL);
		window = win;
		render = r;
	}

	void runFunction() override {
		action(render, pass);
	}
};

#endif