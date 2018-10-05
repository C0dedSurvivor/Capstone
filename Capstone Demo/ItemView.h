#ifndef ITEMV_H
#define ITEMV_H

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "MedicineItem.h"
#include "Equippable.h"
#include "Item.h"

class ItemView : public sf::Drawable, public sf::Transformable {
public:
	std::shared_ptr<sf::Font> font;
	sf::Text name;
	sf::Text amt;
	sf::RectangleShape bg;

	ItemView(std::shared_ptr<sf::Font> f) {
		font = f;

		name.setFont(*font);
		name.setFillColor(sf::Color::Black);
		name.setPosition(sf::Vector2f(20, 17));

		amt.setFont(*font);
		amt.setFillColor(sf::Color::Black);
		amt.setPosition(sf::Vector2f(360, 17));

		bg.setSize(sf::Vector2f(600, 64));
		bg.setFillColor(sf::Color::Yellow);
		bg.setOutlineColor(sf::Color(204, 163, 0, 255));
		bg.setOutlineThickness(-3.0f);
		bg.setPosition(0, 0);
	}

	void update() {
		name.setString("");
		amt.setString("");
	}

	void update(Item i) {
		name.setString(i.name);
		amt.setString(std::to_string(i.amt));
		if (i.amt < 10) {
			amt.setPosition(sf::Vector2f(580, 17));
		} else if (i.amt < 100) {
			amt.setPosition(sf::Vector2f(562, 17));
		} else {
			amt.setPosition(sf::Vector2f(544, 17));
		}
	}

	void update(MedicineItem i) {
		name.setString(i.name);
		amt.setString(std::to_string(i.amt));
		if (i.amt < 10) {
			amt.setPosition(sf::Vector2f(580, 17));
		}
		else if (i.amt < 100) {
			amt.setPosition(sf::Vector2f(562, 17));
		}
		else {
			amt.setPosition(sf::Vector2f(544, 17));
		}
	}

	void update(Equippable i) {
		name.setString(i.name);
		amt.setString(std::to_string(i.amt));
		if (i.amt < 10) {
			amt.setPosition(sf::Vector2f(580, 17));
		}
		else if (i.amt < 100) {
			amt.setPosition(sf::Vector2f(562, 17));
		}
		else {
			amt.setPosition(sf::Vector2f(544, 17));
		}
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(bg, states);
		target.draw(name, states);
		target.draw(amt, states);
	}
};

#endif