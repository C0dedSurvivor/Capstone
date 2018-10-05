#ifndef MPLAYER_H
#define MPLAYER_H

class MapPlayer : public sf::Drawable, public sf::Transformable {
public:
	sf::Texture playerTexture;
	sf::Sprite player;

	sf::Vector2f pos;
	sf::Vector2f size;
	char facing = 'U';

	MapPlayer() {
		size.x = 16;
		size.y = 16;
		playerTexture.loadFromFile("Player.png");
		player.setTexture(playerTexture);
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(player, states);
	}

};

#endif