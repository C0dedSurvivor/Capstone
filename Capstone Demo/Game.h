#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <functional>
#include "Map.h"
#include "MapPlayer.h"
#include "GUISwitchButton.h"
#include "Renderer.h"
#include "EncounterSpace.h"
#include "BattleManager.h"
#include "Inventory.h"

class Game {
public:
	sf::Event windowEvent;
	//sf::Font gameFont;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Inventory> inventory;

	std::vector<std::unique_ptr<Button>> buttons;

	std::vector<std::shared_ptr<Player>> playerList;

	bool isRunning = true;
	bool inBattle = false;
	bool canMove = true;
	bool inMenu = false;

	Game();
	~Game();

	void run();
	void makeLevels();
	void itsHighNoon();
	bool collision(char d);
	void checkBattle();
	void enterBattle(std::string s);
};

#endif