#ifndef BATTLEM_H
#define BATTLEM_H

#include <string>

class BattleMove {
public:
	std::string moveType;
	int user;
	bool target[8] = {false, false, false, false, false, false, false, false};

	BattleMove() {

	}

	BattleMove(std::string m, int u, int t) {
		moveType = m;
		user = u;
		target[t] = true;
	}
};

#endif