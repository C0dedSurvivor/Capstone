#ifndef BATTLEG_H
#define BATTLEG_H

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Battle.h"
#include "ResourceBar.h"

class BattleGraphics {
public:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Battle> battle;

	int openGUI = 0;

	int selectedPlayer = -1;

	//graphics skeletons
	sf::Texture contButtonTexture;
	sf::Sprite contButton;

	sf::Texture battleMenuTexture;
	sf::Sprite battleMenu;

	sf::Texture player;
	sf::Sprite p1;
	sf::Sprite p2;
	sf::Sprite p3;

	sf::Texture e1t;
	sf::Texture e2t;
	sf::Texture e3t;
	sf::Texture e4t;
	sf::Sprite e1;
	sf::Sprite e2;
	sf::Sprite e3;
	sf::Sprite e4;

	sf::Texture backgroundT;
	sf::Sprite background;

	sf::Texture textBoxT;
	sf::Sprite textBox;

	sf::RectangleShape discsMenu;

	bool attachedBars = false;

	ResourceBar p1H;
	ResourceBar p2H;
	ResourceBar p3H;
	ResourceBar e1H;
	ResourceBar e2H;
	ResourceBar e3H;
	ResourceBar e4H;

	sf::Font font;
	sf::Text battleText;
	sf::Clock textTimer;
	int textTime = 1;

	BattleGraphics(const std::shared_ptr<sf::RenderWindow>& w, const std::shared_ptr<Battle>& b) : window(w), battle(b) {
		setup();
	}

	void setup() {
		if (!font.loadFromFile("arial.ttf"))
		{
			// error...
		}
		battleText.setFont(font);
		battleText.setFillColor(sf::Color::Black);
		battleText.setCharacterSize(20);
		battleText.setPosition(sf::Vector2f(210, 510));
		if (!player.loadFromFile("BattlePlayer.png")) {}
		p1.setTexture(player);
		if (battle->nOfPlayers > 1) {
			p2.setTexture(player);
			if (battle->nOfPlayers > 2) {
				//if there are 3 players
				p3.setTexture(player);
				p1.setPosition(sf::Vector2f(20, 40));
				p2.setPosition(sf::Vector2f(47, 222));
				p3.setPosition(sf::Vector2f(20, 404));
			}
			else {
				//if there are 2 players
				p1.setPosition(sf::Vector2f(20, 149));
				p2.setPosition(sf::Vector2f(20, 295));
			}
		}
		else {
			//if there is one player
			p1.setPosition(sf::Vector2f(20, 222));
		}

		if (!e1t.loadFromFile(battle->pawns.at(battle->nOfPlayers)->name + ".png")) {}
		e1.setTexture(e1t);
		if (battle->nOfEnemies > 1) {
			if (!e2t.loadFromFile(battle->pawns.at(battle->nOfPlayers + 1)->name + ".png")) {}
			e2.setTexture(e2t);
			if (battle->nOfEnemies > 2) {
				if (!e3t.loadFromFile(battle->pawns.at(battle->nOfPlayers + 2)->name + ".png")) {}
				e3.setTexture(e3t);
				if (battle->nOfEnemies > 3) {
					//if there are 4 enemies
					if (!e4t.loadFromFile(battle->pawns.at(battle->nOfPlayers + 3)->name + ".png")) {}
					e4.setTexture(e4t);
					e1.setPosition(sf::Vector2f(652, 4));
					e2.setPosition(sf::Vector2f(652, 149));
					e3.setPosition(sf::Vector2f(652, 295));
					e4.setPosition(sf::Vector2f(652, 440));
				}
				else {
					//if there are 3 enemies
					e1.setPosition(sf::Vector2f(652, 40));
					e2.setPosition(sf::Vector2f(652, 222));
					e3.setPosition(sf::Vector2f(652, 404));
				}
			}
			else {
				//if there are 2 enemies
				e1.setPosition(sf::Vector2f(652, 149));
				e2.setPosition(sf::Vector2f(652, 295));
			}
		}
		else {
			//if there is one enemy
			e1.setPosition(sf::Vector2f(652, 222));
		}

		if (!backgroundT.loadFromFile("BattleBackground.png")) {}
		background.setTexture(backgroundT);
		background.setPosition(sf::Vector2f(0, 0));

		//gui
		if (!textBoxT.loadFromFile("BattleTextBox.png")) {}
		textBox.setTexture(textBoxT);
		textBox.setPosition(sf::Vector2f(150, 500));

		//battle menu
		if (!battleMenuTexture.loadFromFile("BattleMenuFull.png")) {}
		battleMenuTexture.setSmooth(true);

		battleMenu.setTexture(battleMenuTexture);
		battleMenu.setPosition(sf::Vector2f(148, 40));

		//battle menu
		if (!contButtonTexture.loadFromFile("Continue.png")) {}

		contButton.setTexture(contButtonTexture);
		contButton.setPosition(sf::Vector2f(300, 250));

		//discs menu
		discsMenu.setSize(sf::Vector2f(500, 400));
		discsMenu.setFillColor(sf::Color::White);
		discsMenu.setPosition(sf::Vector2f(150, 100));
		discsMenu.setOutlineThickness(-10.0f);
		discsMenu.setOutlineColor(sf::Color::Black);
	}

	void attachBars() {
		if (battle->nOfPlayers == 1) {
			p1H = ResourceBar(28, 316, battle->pawns.at(0)->curHealth, battle->pawns.at(0)->maxHealth);
		}
		if (battle->nOfPlayers == 2) {
			p1H = ResourceBar(28, 243, battle->pawns.at(0)->curHealth, battle->pawns.at(0)->maxHealth);
			p2H = ResourceBar(28, 389, battle->pawns.at(1)->curHealth, battle->pawns.at(1)->maxHealth);
		}
		if (battle->nOfPlayers == 3) {
			p1H = ResourceBar(28, 134, battle->pawns.at(0)->curHealth, battle->pawns.at(0)->maxHealth);
			p2H = ResourceBar(55, 316, battle->pawns.at(1)->curHealth, battle->pawns.at(1)->maxHealth);
			p3H = ResourceBar(28, 498, battle->pawns.at(2)->curHealth, battle->pawns.at(2)->maxHealth);
		}
		if (battle->nOfEnemies == 1) {
			e1H = ResourceBar(660, 316, battle->pawns.at(battle->nOfPlayers)->curHealth, battle->pawns.at(battle->nOfPlayers)->maxHealth);
		}
		if (battle->nOfEnemies == 2) {
			e1H = ResourceBar(660, 243, battle->pawns.at(battle->nOfPlayers)->curHealth, battle->pawns.at(battle->nOfPlayers)->maxHealth);
			e2H = ResourceBar(660, 389, battle->pawns.at(battle->nOfPlayers + 1)->curHealth, battle->pawns.at(battle->nOfPlayers + 1)->maxHealth);
		}
		if (battle->nOfEnemies == 3) {
			e1H = ResourceBar(660, 134, battle->pawns.at(battle->nOfPlayers)->curHealth, battle->pawns.at(battle->nOfPlayers)->maxHealth);
			e2H = ResourceBar(660, 316, battle->pawns.at(battle->nOfPlayers + 1)->curHealth, battle->pawns.at(battle->nOfPlayers + 1)->maxHealth);
			e3H = ResourceBar(660, 498, battle->pawns.at(battle->nOfPlayers + 2)->curHealth, battle->pawns.at(battle->nOfPlayers + 2)->maxHealth);
		}
		if (battle->nOfEnemies == 4) {
			e1H = ResourceBar(660, 98, battle->pawns.at(battle->nOfPlayers)->curHealth, battle->pawns.at(battle->nOfPlayers)->maxHealth);
			e2H = ResourceBar(660, 243, battle->pawns.at(battle->nOfPlayers + 1)->curHealth, battle->pawns.at(battle->nOfPlayers + 1)->maxHealth);
			e3H = ResourceBar(660, 389, battle->pawns.at(battle->nOfPlayers + 2)->curHealth, battle->pawns.at(battle->nOfPlayers + 2)->maxHealth);
			e4H = ResourceBar(660, 534, battle->pawns.at(battle->nOfPlayers + 3)->curHealth, battle->pawns.at(battle->nOfPlayers + 3)->maxHealth);
		}
		attachedBars = true;
	}

	void drawGraphics() {
		// clear the window with green :D
		window->clear(sf::Color::Green);

		window->draw(background);

		if (battle->genedPawns && !attachedBars)
			attachBars();

		// draw everything here
		window->draw(p1);
		if(battle->nOfPlayers > 1)
			window->draw(p2);
		if (battle->nOfPlayers > 2)
			window->draw(p3);
		window->draw(e1);
		if (battle->nOfEnemies > 1)
			window->draw(e2);
		if (battle->nOfEnemies > 2)
			window->draw(e3);
		if (battle->nOfEnemies > 3)
			window->draw(e4);
		if (attachedBars) {
			p1H.update();
			p1H.draw(*window, sf::RenderStates::Default);
			if (battle->nOfPlayers > 1) {
				p2H.update();
				p2H.draw(*window, sf::RenderStates::Default);
				if (battle->nOfPlayers > 2){
					p3H.update();
					p3H.draw(*window, sf::RenderStates::Default);
				}
			}
			e1H.update();
			e1H.draw(*window, sf::RenderStates::Default);
			if (battle->nOfEnemies > 1) {
				e2H.update();
				e2H.draw(*window, sf::RenderStates::Default);
				if (battle->nOfEnemies > 2) {
					e3H.update();
					e3H.draw(*window, sf::RenderStates::Default);
					if (battle->nOfEnemies > 3) {
						e4H.update();
						e4H.draw(*window, sf::RenderStates::Default);
					}
				}
			}
		}
		window->draw(textBox);
		std::string s = battleText.getString();
		if (s.compare(battle->textPass) != 0 && textTimer.getElapsedTime().asMilliseconds() >= textTime) {
			battleText.setString(battle->textPass.substr(0, battleText.getString().getSize() + 1));
			textTimer.restart();
		}
		window->draw(battleText);
		selectedPlayer = battle->selectedPlayer;
		if (selectedPlayer != -1) {
			window->draw(battleMenu);
		}
		if (battle->playersChosen) {
			window->draw(contButton);
		}
		if (battle->moveSelected > 20) {
			openGUI = 0;
		}
		if (openGUI == 1) {
			window->draw(discsMenu);
		}

		// end the current frame
		window->display();
	}

	void playerMenuPos(int pos)
	{
		if (battle->battleState.compare("playerMoves") == 0) {
			selectedPlayer = pos;
			battle->selectedPlayer = pos;
			battle->moveSelected = -1;
			if (selectedPlayer == 0) {
				if(battle->nOfPlayers == 1)
					battleMenu.setPosition(sf::Vector2f(148, 222));
				if (battle->nOfPlayers == 2)
					battleMenu.setPosition(sf::Vector2f(148, 149));
				if (battle->nOfPlayers == 3)
					battleMenu.setPosition(sf::Vector2f(148, 40));
			}
			else if (selectedPlayer == 1) {
				if (battle->nOfPlayers == 2)
					battleMenu.setPosition(sf::Vector2f(148, 295));
				if (battle->nOfPlayers == 3)
					battleMenu.setPosition(sf::Vector2f(175, 222));
			}
			else if (selectedPlayer == 2) {
				battleMenu.setPosition(sf::Vector2f(148, 404));
			}
		}
	}

	void switchGUI(int gui) {
		if (gui == 1) {
			battle->moveSelected = -1;
		}
		openGUI = gui;
	}
};

#endif