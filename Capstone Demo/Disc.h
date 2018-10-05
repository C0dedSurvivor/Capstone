#ifndef DISC_H
#define DISC_H

#include <vector>
#include "StatChange.h"

/*
defense: neutral = attack: bad = attack
attack: neutral = magic: bad = defense
magic: neutral = defense: bad = attack
*/

class Discs {
public:
	std::string discName;
	std::string nickname;
	//1 for attack, 2 for magic, 3 for defense: denotes child class type for dynamic_casting
	int discType;
	//1 for single target, 2 for all enemies;
	int targetType;
	int ramUse;
	int romUse;
	std::vector<statChange> statChanges;

	virtual ~Discs() {};
};

#endif