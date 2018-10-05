#ifndef MAGICDISC_H
#define MAGICDISC_H

#include "Disc.h"

class MagicDisc : public Discs {
public:
	//air, fire, earth, water, light, dark
	int type[6];
	MagicDisc() {};

	MagicDisc(std::string name, int rom, int ram, int types[6], std::vector<statChange> stat = {}) {
		nickname = name;
		discName = name;
		discType = 2;
		ramUse = ram;
		romUse = rom;
		for (int i = 0; i < 6; i++) {
			type[i] = types[i];
		}
		statChanges = stat;
	}
};

#endif