#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>
#include "StatChange.h"
#include "Effect.h"
#include "AttackDisc.h"
#include "MagicDisc.h"
#include "DefenseDisc.h"
#include "ItemMove.h"
#include "Player.h"
#include "Enemy.h"

class Move {
public:
	int user;
	bool target[8];

	std::string type;

	bool miss = false;
	int initialDamage = 0;
	int reflectDamage = 0;
	int extraDamage = 0;
	std::string source = "";
	int stealHeal = 0;
	bool healDenied = false;
	int healing = 0;
	int shield = 0;
	//sorted by strength then stat affected
	//stat it affects (1=pAtk, 2=mAtk, 3=pDef, 4=Mdef, 5=Speed, 6=Accuracy), strength of the buff/debuff(> 1 for buff, < 1 for debuff), chance of it happening (in decimal)
	std::vector<statChange> statChanges;
	//pretty much only status effects :D
	std::vector<Effect> effects;

	Move(int u, bool t[]) {
		user = u;
		for (int i = 0; i < 8; i++) {
			target[i] = t[i];
		}
	}

	//basic attack
	void generateMove(std::vector<std::shared_ptr<BattleStats>> &p) {
		type = "Basic";
		for (int i = 0; i < 8; i++) {
			if (target[i]) {
				initialDamage = (p.at(user)->pAtk * p.at(user)->pAtkMod * 10.0f) / (p.at(i)->pDef * p.at(i)->pDefMod);
				break;
			}
		}
	}

	void generateMove(std::vector<std::shared_ptr<BattleStats>> &p, AttackDisc disc) {
		type = disc.nickname;
		for (int i = 0; i < 8; i++) {
			if (target[i]) {
				double def = p.at(i)->pDef * p.at(i)->pDefMod;
				if (disc.defPen >= 1) {
					if (def - disc.defPen < def / 2.0f) {
						def /= 2.0f;
					}
					else {
						def -= disc.defPen;
					}
				}
				else if (disc.defPen < 1) {
					if (disc.defPen > 0.65) {
						def /= 2.0f;
					}
					else {
						def *= disc.defPen;
					}
				}
				initialDamage = (p.at(user)->pAtk * p.at(user)->pAtkMod * disc.multiplier * 10.0f) / def;
				break;
			}
		}
	}

	void generateMove(std::vector<std::shared_ptr<BattleStats>> &p, MagicDisc disc) {
		type = disc.nickname;
		for (int i = 0; i < 8; i++) {
			if (target[i]) {
				initialDamage = (p.at(user)->mAtk * p.at(user)->mAtkMod * 10.0f) / (p.at(i)->mDef * p.at(i)->mDefMod);
				break;
			}
		}
	}

	void generateMove(std::vector<std::shared_ptr<BattleStats>> &p, DefenseDisc disc) {

	}

	void activateEffect() {

	}
};

#endif