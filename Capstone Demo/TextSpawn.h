#ifndef TEXTSPAWN_H
#define TEXTSPAWN_H
#include <SFML\Graphics.hpp>
#include <math.h>
class TextSpawn {
public:
	int x, y;
	sf::Text floater;
	TextSpawn() {}
	TextSpawn(std::string tempText, int tempX, int tempY) {
		x = tempX;
		y = tempY;
		floater.setString(tempText);
		floater.setCharacterSize(34);
		floater.setFillColor(sf::Color::Black);
		floater.setStyle(sf::Text::Bold);
		floater.setPosition(sf::Vector2f(tempX, tempY));
	}

	void move() {
		if (y == floater.getPosition().y + 60) {
			//floater.setFillColor(sf::Color::Transparent);
			//floater.setOutlineColor(sf::Color::Transparent);
			floater.setPosition(sf::Vector2f(x, y));
		}
		else {
			floater.setPosition(sf::Vector2f(x + cos((floater.getPosition().y - 1) / 6.4) * 5, floater.getPosition().y - 1));
		}
	}
};

#endif