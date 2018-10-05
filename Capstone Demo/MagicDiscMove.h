#ifndef MAGICDISCM_H
#define MAGICDISCM_H
#include "MagicDisc.h";
#include "BattleMove.h";
class MagicDiscMove : public BattleMove {
public:
	MagicDisc disc;
	//used if spell is single target
	MagicDiscMove(MagicDisc passDisc, int targeted, int userP) {
		disc = passDisc;
		user = userP;
		target[targeted] = true;
		moveType = "mdisc";
	}
	//used if spell affects multiple allies
	MagicDiscMove(MagicDisc passDisc, int targeted[], int userP) {
		disc = passDisc;
		user = userP;
		for (int i = 0; i < sizeof(targeted); i++) {
			target[targeted[i]] = true;
		}
		moveType = "mdisc";
	}
};
#endif