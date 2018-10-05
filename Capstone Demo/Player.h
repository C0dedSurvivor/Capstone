#ifndef PLAYER_H
#define PLAYER_H

#include "BattleStats.h"
#include "AttackDisc.h"
#include "DefenseDisc.h"
#include "MagicDisc.h"
#include <vector>
#include <memory>
#include <iostream>

class Player : public BattleStats{
public:
	int level;
	int exp;
	int overclock;
	int ram;
	int rom;
	//1 for attack, 2 for magic, 3 for defense
	int discAffinity;
	std::vector<std::shared_ptr<Discs>> equippedDiscs;

	Player() {

	}

	void genRandomPlayer();
	void gainEXP(int expGain);
	int expPerLevel();
};

#endif