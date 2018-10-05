#ifndef DOOR_H
#define DOOR_H

#include <SFML/Graphics.hpp>
class Door {
public:
	sf::Vector2f pos;
	char direction;
	bool open = false;

	Door(){}

	Door(int x, int y, char d) {
		pos.x = x;
		pos.y = y;
		direction = d;
	}
};

#endif