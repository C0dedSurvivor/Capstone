#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <string>
#include <Windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <thread>
#include "Battle.h"
#include "Button.h"
#include "VoidIntButton.h"
#include "BattleGraphics.h"
#include "VoidIntGButton.h"

class BattleManager{
public:
	std::shared_ptr<Battle> battle;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<BattleGraphics> graphics;

	std::vector<std::unique_ptr<Button>> buttons;

	bool battleOver = false;

	BattleManager(const std::shared_ptr<sf::RenderWindow>& w, std::vector<std::shared_ptr<Player>> playerList) : window(w) {
		battle = std::shared_ptr<Battle>(new Battle(playerList));
		startBattle();
	}
	BattleManager(const std::shared_ptr<sf::RenderWindow>& w, std::vector<std::shared_ptr<Player>> playerList, std::string specCond) : window(w) {
		battle = std::shared_ptr<Battle>(new Battle(playerList, specCond));
		startBattle();
	}

	void startBattle(){


		graphics = std::shared_ptr<BattleGraphics>(new BattleGraphics(window, battle));


		//button 0
		VoidIntGButton p1Select(20, 40, 128, 128, window, graphics);
		p1Select.action = &BattleGraphics::playerMenuPos;
		p1Select.pass = 0;
		//button 1
		VoidIntGButton p2Select(47, 222, 128, 128, window, graphics);
		p2Select.action = &BattleGraphics::playerMenuPos;
		p2Select.pass = 1;
		//button 2
		VoidIntGButton p3Select(20, 404, 128, 128, window, graphics);
		p3Select.action = &BattleGraphics::playerMenuPos;
		p3Select.pass = 2;
		
		if (battle->nOfPlayers == 1) {
			p1Select.setPosition(20, 222);
			p2Select.enabled = false;
			p3Select.enabled = false;
		}
		if (battle->nOfPlayers == 2) {
			p1Select.setPosition(20, 149);
			p2Select.setPosition(20, 295);
			p3Select.enabled = false;
		}
		buttons.emplace_back(std::make_unique<VoidIntGButton>(p1Select));
		buttons.emplace_back(std::make_unique<VoidIntGButton>(p2Select));
		buttons.emplace_back(std::make_unique<VoidIntGButton>(p3Select));
		


		///code this plz///button 3
		VoidIntButton basicAttackSelect(148 + 30, 40 + 3, 51, 20, window, battle);
		basicAttackSelect.action = &Battle::enterMoveType;
		basicAttackSelect.pass = 1;
		basicAttackSelect.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntButton>(basicAttackSelect));

		///code this plz///button 4
		VoidIntGButton discSelect(148 + 40, 40 + 27, 51, 20, window, graphics);
		discSelect.action = &BattleGraphics::switchGUI;
		discSelect.pass = 1;
		discSelect.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntGButton>(discSelect));

		///code this plz///button 5
		VoidIntGButton skillSelect(148 + 44, 40 + 54, 51, 20, window, graphics);
		skillSelect.action = &BattleGraphics::playerMenuPos;
		skillSelect.pass = 2;
		skillSelect.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntGButton>(skillSelect));

		///code this plz///button 6
		VoidIntGButton itemSelect(148 + 40, 40 + 81, 51, 20, window, graphics);
		itemSelect.action = &BattleGraphics::playerMenuPos;
		itemSelect.pass = 2;
		itemSelect.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntGButton>(itemSelect));

		///code this plz///button 7
		VoidIntGButton runSelect(148 + 30, 40 + 105, 51, 20, window, graphics);
		runSelect.action = &BattleGraphics::playerMenuPos;
		runSelect.pass = 3;
		runSelect.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntGButton>(runSelect));

		///code this plz///button 8
		VoidIntButton e1(652, 4, 128, 128, window, battle);
		e1.action = &Battle::targetEnemy;
		e1.pass = 0;
		e1.enabled = false;
		///code this plz///button 9
		VoidIntButton e2(652, 149, 128, 128, window, battle);
		e2.action = &Battle::targetEnemy;
		e2.pass = 1;
		e2.enabled = false;
		///code this plz///button 10
		VoidIntButton e3(652, 295, 128, 128, window, battle);
		e3.action = &Battle::targetEnemy;
		e3.pass = 2;
		e3.enabled = false;
		///code this plz///button 11
		VoidIntButton e4(652, 440, 128, 128, window, battle);
		e4.action = &Battle::targetEnemy;
		e4.pass = 3;
		e4.enabled = false;

		if (battle->nOfEnemies == 1) {
			e1.setPosition(652, 222);
		}
		if (battle->nOfEnemies == 2) {
			e1.setPosition(652, 149);
			e2.setPosition(652, 295);
		}
		if (battle->nOfEnemies == 3) {
			e1.setPosition(652, 40);
			e2.setPosition(652, 202);
			e3.setPosition(652, 444);
		}
		buttons.emplace_back(std::make_unique<VoidIntButton>(e1));
		buttons.emplace_back(std::make_unique<VoidIntButton>(e2));
		buttons.emplace_back(std::make_unique<VoidIntButton>(e3));
		buttons.emplace_back(std::make_unique<VoidIntButton>(e4));

		///code this plz///button 12
		VoidIntButton contButton(300, 250, 200, 100, window, battle);
		contButton.action = &Battle::continueChoice;
		contButton.pass = 0;
		contButton.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntButton>(contButton));

		///code this plz///button 13
		VoidIntButton disc1Select(150, 100, 250, 200, window, battle);
		disc1Select.action = &Battle::enterMoveType;
		disc1Select.pass = 21;
		disc1Select.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntButton>(disc1Select));

		///code this plz///button 14
		VoidIntButton disc2Select(401, 100, 249, 200, window, battle);
		disc2Select.action = &Battle::enterMoveType;
		disc2Select.pass = 22;
		disc2Select.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntButton>(disc2Select));

		///code this plz///button 15
		VoidIntButton disc3Select(148 + 30, 40 + 3, 51, 20, window, battle);
		disc3Select.action = &Battle::enterMoveType;
		disc3Select.pass = 23;
		disc3Select.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntButton>(disc3Select));

		///code this plz///button 16
		VoidIntButton disc4Select(148 + 30, 40 + 3, 51, 20, window, battle);
		disc4Select.action = &Battle::enterMoveType;
		disc4Select.pass = 24;
		disc4Select.enabled = false;
		buttons.emplace_back(std::make_unique<VoidIntButton>(disc4Select));

		std::thread battleLoop(&Battle::start, battle);

		battle->battleState = "playerMoves";

		while (window->isOpen() && !battleOver)
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window->pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed || battle->battleState.compare("end") == 0) {
					battleOver = true;
				}
				if (event.type == sf::Event::MouseButtonReleased) {
					//clicked on buttons
					if (event.mouseButton.button == sf::Mouse::Left) {
						for (int i = 0; i < buttons.size(); i++) {
							if (buttons.at(i)->enabled && buttons.at(i)->checkButton()) {
								buttons.at(i)->runFunction();
								break;
							}
						}
					}
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						//disks
						if (graphics->openGUI == 1)
							graphics->openGUI = 0;
					}
					//deals with manipulating battle text
					if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Z) {
						std::string s = graphics->battleText.getString();
						if (s.compare(battle->textPass) != 0) {
							graphics->battleText.setString(battle->textPass);
						}
						else {
							graphics->battleText.setString("");
							battle->textPass = "";
						}
					}
				}
			}
			if (battle->battleState.compare("playerMoves") == 0) {
				if (graphics->selectedPlayer == 0) {
					//BasicAttackSelect
					if (battle->nOfPlayers == 1) {
						buttons.at(3)->setPosition(148 + 30, 222 + 3);
						buttons.at(4)->setPosition(148 + 40, 222 + 27);
					}
					else if (battle->nOfPlayers == 2) {
						buttons.at(3)->setPosition(148 + 30, 149 + 3);
						buttons.at(4)->setPosition(148 + 40, 149 + 27);
					}
					if (battle->nOfPlayers == 3) {
						buttons.at(3)->setPosition(148 + 30, 40 + 3);
						buttons.at(4)->setPosition(148 + 40, 40 + 27);
					}
					buttons.at(3)->enabled = true;
					buttons.at(4)->enabled = true;
				}
				else if (graphics->selectedPlayer == 1) {
					if (battle->nOfPlayers == 2) {
						buttons.at(3)->setPosition(148 + 30, 295 + 3);
						buttons.at(4)->setPosition(148 + 40, 295 + 27);
					}
					else {
						buttons.at(3)->setPosition(175 + 30, 222 + 3);
						buttons.at(4)->setPosition(175 + 40, 222 + 27);

					}
					buttons.at(3)->enabled = true;
					buttons.at(4)->enabled = true;
				}
				else if (graphics->selectedPlayer == 2) {
					buttons.at(3)->setPosition(148 + 30, 404 + 3);
					buttons.at(4)->setPosition(148 + 40, 404 + 27);
					buttons.at(3)->enabled = true;
					buttons.at(4)->enabled = true;
				}
			}
			if (graphics->openGUI == 1) {
				BattleStats* p = battle->pawns.at(graphics->selectedPlayer).get();
				if (dynamic_cast<Player*>(p)->equippedDiscs.size() > 0) {
					buttons.at(13)->enabled = true;
					if (dynamic_cast<Player*>(p)->equippedDiscs.size() > 1) {
						buttons.at(14)->enabled = true;
						if (dynamic_cast<Player*>(p)->equippedDiscs.size() > 2) {
							buttons.at(15)->enabled = true;
							if (dynamic_cast<Player*>(p)->equippedDiscs.size() > 3) {
								buttons.at(16)->enabled = true;
							}
						}
					}
				}
			}
			else {
				buttons.at(13)->enabled = false;
				buttons.at(14)->enabled = false;
				buttons.at(15)->enabled = false;
				buttons.at(16)->enabled = false;
			}
			if (battle->moveSelected != -1) {
				buttons.at(8)->enabled = true;
				if(battle->nOfEnemies > 1)
					buttons.at(9)->enabled = true;
				if (battle->nOfEnemies > 2)
					buttons.at(10)->enabled = true;
				if (battle->nOfEnemies > 3)
					buttons.at(11)->enabled = true;
			}
			else {
				buttons.at(8)->enabled = false;
				buttons.at(9)->enabled = false;
				buttons.at(10)->enabled = false;
				buttons.at(11)->enabled = false;
			}

			if (battle->playersChosen && graphics->openGUI == 0)
				buttons.at(12)->enabled = true;
			else
				buttons.at(12)->enabled = false;

			graphics->drawGraphics();
		}
		battleLoop.join();
		return;
	}
};

#endif