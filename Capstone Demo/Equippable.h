#ifndef EITEM_H
#define EITEM_H

#include <string>
#include "Item.h"

class Equippable : public Item{
public:
	double armor;
	double mArmor;
	double damageBoost;
	double mDamageBoost;

	Equippable(std::string n) {
		name = n;
		amt = 1;
	}
};

#endif