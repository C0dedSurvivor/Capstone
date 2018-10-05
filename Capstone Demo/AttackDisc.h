#ifndef ATTACKDISC_H
#define ATTACKDISC_H

#include "Disc.h"
#include <vector>

class AttackDisc : public Discs {
public:
	double multiplier;
	// < 1 for % defense pen, > 1 for flat value (either one caps out at 50% pen)
	double defPen;

	AttackDisc() {};

	AttackDisc(std::string name, int rom, int ram, double multi, double pen = 0, std::vector<statChange> stat = {}) {
		discName = name;
		nickname = name;
		discType = 1;
		ramUse = ram;
		romUse = rom;
		multiplier = multi;
		defPen = pen;
		statChanges = stat;
	}
};

#endif