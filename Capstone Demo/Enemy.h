#ifndef ENEMY_H
#define ENEMY_H

#define monsters 6
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "BattleStats.h"

extern const std::string monsterList[monsters][7];

class Enemy : public BattleStats{
public:
	int level;
	//0 is normal, 1 is armored, 2 is glitched
	int variant;

	Enemy() {
		if(rand() % 2 == 0)
			name = "slime";
		else
			name = "slime2";
		variant = 0;
		level = 1;
		ITSALIVE();
	}

	Enemy(std::string monster, int lvl, int v) {
		name = monster;
		level = lvl;
		variant = v;
		ITSALIVE();
	}

	void ITSALIVE();
	void die();

};

#endif