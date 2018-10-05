#ifndef BATTLE_H
#define BATTLE_H

#include <utility>
#include <string>
#include <iostream>
#include <cctype>
#include <cmath>
#include <memory>
#include <vector>
#include <time.h>
#include <tuple>
#include <array>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "BattleStats.h"
#include "Disc.h"
#include "AttackDisc.h"
#include "MagicDisc.h"
#include "Item.h"
#include "EffectHandler.h"
#include "Move.h"
#include "BattleMove.h"

class Battle {
public:
	int nOfPlayers;
	int nOfEnemies;

	std::string battleState = "state";

	//Player pPawns[4];
	//Enemy ePawns[4];
	//BattleStats pawns[8];
	std::vector<std::shared_ptr<BattleStats>> pawns;

	std::vector<std::unique_ptr<BattleMove>> moveInputList;

	std::vector<std::unique_ptr<Move>> moveExecutableList;

	std::vector<std::pair<std::string, int>> convList;

	bool playersChosen = false;
	bool cont = false;
	bool genedPawns = false;
	std::string textPass = "";

	int selectedPlayer = -1;
	int moveSelected = -1;
	int selectedEnemy = -1;

	sf::Music music;

	Battle() {} //temporary declaration

	Battle(std::vector<std::shared_ptr<Player>> &p)
	{
		for (int i = 0; i < p.size(); i++) {
			pawns.emplace_back(p.at(i));
		}
		nOfPlayers = p.size();
		nOfEnemies = rand() % (nOfPlayers + 1) + 1;
		generateEnemies(nOfEnemies);
		if (!music.openFromFile("Sound/Music/10-let-the-battles-begin-ogg.ogg")) { }
		music.play();
	};
	Battle(std::vector<std::shared_ptr<Player>> &p, std::string specCond)
	{
		for (int i = 0; i < p.size(); i++) {
			pawns.emplace_back(p.at(i));
		}
		nOfPlayers = p.size();
		if (specCond.compare("Boss1") == 0) {
			nOfEnemies = 3;
			generateEnemies("Boss1");
		}
		if (!music.openFromFile("Sound/Music/10-let-the-battles-begin-ogg.ogg")) {}
		music.play();
	};
	void start();
	void battle();
	void end(std::string t);
	void generateEnemies(int eCount);
	void generateEnemies(std::string specBattleCond);
	void playerChoosesMoves();
	void enemiesChooseMoves();
	void setTurnOrder();
	void enterMoveType(int i);
	void targetEnemy(int i);
	void makeMoves();
	void executeMoves();
	void continueChoice(int i);
};

#endif