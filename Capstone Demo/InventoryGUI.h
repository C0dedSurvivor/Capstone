#ifndef IGUI_H
#define IGUI_H

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Item.h"
#include "ItemView.h"

class InventoryGUI : public sf::Drawable, public sf::Transformable {
public:
	std::vector<Item>* inv;
	std::vector<ItemView> view;
	std::shared_ptr<sf::Font> font;
	int showLength;
	int top = 0;

	InventoryGUI() {}

	InventoryGUI(int x, int y, std::vector<Item>* v, int s) {
		setPosition(x, y);
		inv = v;
		showLength = s;
		font = std::shared_ptr<sf::Font>(new sf::Font());
		if (!font->loadFromFile("arial.ttf"))
		{
			// error...
		}
		for (int i = 0; i < s; i++) {
			auto j = ItemView(font);
			j.setPosition(0, 64 * i);
			view.emplace_back(j);
		}
		update();
	}

	void up() {
		if (top != 0)
			top--;
		update();
	}

	void down() {
		if (top + showLength < inv->size())
			top++;
		update();
	}

	void update() {
		for (int i = top; i < top + showLength; i++) {
			if (i < inv->size()) {
				view.at(i - top).update(inv->at(i));
			}
			else {
				view.at(i - top).update();
			}
		}
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		states.transform.translate(getPosition());
		for (int i = 0; i < view.size(); i++) {
			target.draw(view.at(i), states);
			states.transform.translate(0, 64);
		}
	}

};

#endif