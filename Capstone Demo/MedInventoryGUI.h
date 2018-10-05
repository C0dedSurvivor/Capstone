#ifndef IMGUI_H
#define IMGUI_H

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "MedicineItem.h"
#include "ItemView.h"

class MedInventoryGUI : public sf::Drawable, public sf::Transformable {
public:
	std::vector<MedicineItem>* invM;
	std::vector<ItemView> view;
	std::shared_ptr<sf::Font> font;
	int showLength;
	int top = 0;

	MedInventoryGUI() {}

	MedInventoryGUI(int x, int y, std::vector<MedicineItem>* v, int s) {
		setPosition(x, y);
		invM = v;
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
		if (top + showLength < invM->size())
			top++;
		update();
	}

	void update() {
		for (int i = top; i < top + showLength; i++) {
			if (i < invM->size()) {
				view.at(i - top).update(invM->at(i));
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