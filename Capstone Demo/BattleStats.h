#ifndef BATTLESTATS_H
#define BATTLESTATS_H

#include <string>
#include <tuple>
#include <time.h>
#include <memory>

class BattleStats {
public:
	std::string name;

	int pAtk; //Physical attack: Affects damage of physical spells and basic attacks
	int mAtk; //Magic attack: Affects damage of magic spells
	int pDef; //Physical defense: Mitigates damage of physical spells and basic attacks
	int mDef; //Magic defense: Mitigates damage of magic spells
	int speed; //Speed: Affects what order you move in during the battle

	//Modifiers to the base stats (buffs and debuffs) only for that battle
	double pAtkMod;
	double mAtkMod;
	double pDefMod;
	double mDefMod;
	double speedMod;
	double accMod;

	std::shared_ptr<int> maxHealth;
	std::shared_ptr<int> curHealth;
	int shield;
	int maxRam;
	int curRam;
	int maxRom;
	int curRom;

	int lifeSteal;
	int magicSap;

	bool isAlive = true;
	bool enteredMove = false;

	BattleStats() {
		reset();
	}

	void reset();
	int heal(double h);
	std::pair<int, int> takeDamage(double d);
	std::string statBuff(int stat, double amount, double chance);
	virtual ~BattleStats() {};
};

#endif