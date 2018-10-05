#ifndef RESOURCEBAR_H
#define RESOURCEBAR_H

#include <SFML/Graphics.hpp>
#include <memory>

class ResourceBar : public sf::Drawable, public sf::Transformable {
public:
	int xPos;
	int yPos;
	int xLength;
	int yLength;
	int iXLength;
	std::shared_ptr<int> maxR;
	std::shared_ptr<int> cur;
	sf::RectangleShape outer;
	sf::RectangleShape inner;

	ResourceBar() {

	}

	ResourceBar(int x, int y, std::shared_ptr<int> c, std::shared_ptr<int> m) : cur(c), maxR(m) {
		xPos = x;
		yPos = y;
		xLength = 110;
		yLength = 30;
		iXLength = 100;
		outer.setFillColor(sf::Color(230, 230, 230));
		outer.setOutlineColor(sf::Color(77, 77, 77));
		outer.setOutlineThickness(-1 * (xLength - iXLength)/2.0f);
		outer.setPosition(xPos, yPos);
		outer.setSize(sf::Vector2f(xLength, yLength));
		inner.setFillColor(sf::Color(204, 0, 0));
		inner.setPosition(xPos + (xLength - iXLength) / 2.0f, yPos + (xLength - iXLength) / 2.0f);
		inner.setSize(sf::Vector2f(iXLength, yLength - (xLength - iXLength)));
	}

	ResourceBar(int xP, int yP, int xL, int yL, int iXL, std::shared_ptr<int> c, std::shared_ptr<int> m) : cur(c), maxR(m) {

	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(outer, states);
		target.draw(inner, states);
	}

	void update() {
		inner.setSize(sf::Vector2f(*cur/(*maxR * 1.0f) * iXLength, inner.getSize().y));
	}

	void link(std::shared_ptr<int> c, std::shared_ptr<int> m) {
		cur = c;
		maxR = m;
	}
};

#endif