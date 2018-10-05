#ifndef EFFECTH_H
#define EFFECTH_H

#include <string>
#include <vector>
#include <memory>
#include <time.h>
#include <array>
#include <unordered_map>
#include "Effect.h"
#include "BattleStats.h"

class EffectHandler {
public:
	const static int textListL = 42;
	std::string text[textListL][2] = { 
		{ "damage", "TARGET took STRENGTH damage!"},
		{ "heal", "TARGET was healed for STRENGTH health!"},
		{ "shield", "TARGET was shielded for STRENGTH damage!"},
		{ "ramGain", "TARGET recovered STRENGTH RAM!"},
		{ "romGain", "TARGET recovered STRENGTH ROM!"},
		{ "paralyzed", "TARGET is paralyzed!"},
		{ "freeze", "TARGET is frozen!"}, 
		{ "burn", "TARGET is burned!"}, 
		{ "poison", "TARGET is poisoned!"}, 
		{ "sleep", "TARGET is asleep!"},
		{ "confusion", "TARGET is confused!"},
		{ "enraged", "TARGET is enraged at USER!"},
		{ "acid", "TARGET's defenses were shredded by acid!"},
		{ "physicalAttackChangeGreatInc", "TARGET's attack was greatly increased!" },
		{ "physicalAttackChangeInc", "TARGET's attack was increased!" },
		{ "physicalAttackChangeDec", "TARGET's attack was decreased!" },
		{ "physicalAttackChangeGreatDec", "TARGET's attack was greatly decreased!" },
		{ "physicalDefenseChangeGreatInc", "TARGET's defense was greatly increased!" },
		{ "physicalDefenseChangeInc", "TARGET's defense was increased!" },
		{ "physicalDefenseChangeDec", "TARGET's defense was decreased!" },
		{ "physicalDefenseChangeGreatDec", "TARGET's defense was greatly decreased!" },
		{ "magicalAttackChangeGreatInc", "TARGET's magical attack was greatly increased!" },
		{ "magicalAttackChangeInc", "TARGET's magical attack was increased!" },
		{ "magicalAttackChangeDec", "TARGET's magical attack was decreased!" },
		{ "magicalAttackChangeGreatDec", "TARGET's magical attack was greatly decreased!" },
		{ "magicalDefenseChangeGreatInc", "TARGET's magical defense was greatly increased!" },
		{ "magicalDefenseChangeInc", "TARGET's magical defense was increased!" },
		{ "magicalDefenseChangeDec", "TARGET's magical defense was decreased!" },
		{ "magicalDefenseChangeGreatDec", "TARGET's magical defense was greatly decreased!" },
		{ "speedChangeGreatInc", "TARGET's speed was greatly increased!" },
		{ "speedChangeInc", "TARGET's speed was increased!" },
		{ "speedChangeDec", "TARGET's speed was decreased!" },
		{ "speedChangeGreatDec", "TARGET's speed was greatly decreased!" },
		{ "accuracyChangeGreatInc", "TARGET's accuracy was greatly increased!" },
		{ "accuracyChangeInc", "TARGET's accuracy was increased!" },
		{ "accuracyChangeDec", "TARGET's accuracy was decreased!" },
		{ "accuracyChangeGreatDec", "TARGET's accuracy was greatly decreased!" },
		{ "lifesteal", "USER stole some health from TARGET!"},
		{ "spellsteal", "USER stole some health from TARGET!" },
		{ "resourceVampRAM", "USER stole some RAM from TARGET!"},
		{ "resourceVampROM", "USER stole some ROM from TARGET!" },
		{ "revive", "TARGET was revived!"}
	};

	//effects without targets that need to be triggered
	std::vector<std::unique_ptr<Effect>> effects;

	//effects with all necessary components to be run immediately
	std::vector<std::unique_ptr<Effect>> immediate;

	std::array<BattleStats, 8>* pawns;

	EffectHandler(std::array<BattleStats, 8>* p)
	{
		pawns = p;
	}
	std::string activateEffect(int p);
	std::vector<Effect> find(std::string effectType, int user);
	void recalcStatMods();
	std::string getString(std::string effect, int target, int user = 0, double strength = 0.0);
	std::string checkCanMove(int target);

};

#endif