#ifndef BTRIGGER_H
#define BTRIGGER_H

#include <SFML/Graphics.hpp>
#include <vector>

class BattleTrigger {
public:
	sf::Vector2f pos;
	std::string specCond;

	BattleTrigger() {}

	BattleTrigger(int x, int y, std::string s) {
		pos.x = x;
		pos.y = y;
		specCond = s;
	}
};

#endif