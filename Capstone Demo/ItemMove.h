#ifndef ITEMM_H
#define ITEMM_H

#include "BattleMove.h"

class ItemMove : public BattleMove {
	//number = amount, decimal = %
	double heal;
	//0 = no status healed, 1 = Memory Wipe(sleeping), 2 = Lag(paralysis), 3 = Overheat(burn), 4 = Fragmentation(poison), 5 = Scripting Virus(confusion), 6 = Enraged, 7 = all
	int statusHeal;

	ItemMove() {
		moveType = "item";
	}
};

#endif