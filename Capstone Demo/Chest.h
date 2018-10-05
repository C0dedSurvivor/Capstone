#ifndef CHEST_H
#define CHEST_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"

class Chest {
public:
	sf::Vector2f pos;
	std::vector<Item> inv;

	Chest() {}

	Chest(int x, int y) {
		pos.x = x;
		pos.y = y;
	}

	Chest(int x, int y, std::vector<Item> i) {
		pos.x = x;
		pos.y = y;
		for (int x = 0; x < i.size(); x++)
			addItem(i.at(x));
	}

	void addItem(Item i) {
		inv.emplace_back(i);
	}
};

#endif