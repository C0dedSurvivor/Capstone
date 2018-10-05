#ifndef STAIRS_H
#define STAIRS_H

#include <SFML/Graphics.hpp>
class Stairs {
public:
	sf::Vector2f pos;
	char direction;
	int targetMap;
	int targetSpawn;

	Stairs(){}

	Stairs(int x, int y, char d, int tM, int tS) {
		pos.x = x;
		pos.y = y;
		direction = d;
		targetMap = tM;
		targetSpawn = tS;
	}
};

#endif