#ifndef EFFECT_H
#define EFFECT_H

class Effect {
public:
	std::string type;
	double strength;

	/*
	“none”
	“chance” (chance to remove each turn, represented by number > 1 & < 100)
	“overTime” (activates each turn for DURATION turns)
	“wait” (waits DURATION turns before activating)
	“infinite” (activates once but can be removed later Ex: stat debuff; activates every turn)
	*/
	std::string durationType;
	int duration;

	/*
	"none"
	"turnStart"
	"onBasic"
	"onSpell"
	"gotHit"
	"hitWithP"
	"hitWithM"
	"immediate"
	"turnEnd"
	*/
	std::string actType;

	/*
	"stat" = all stat changes
	"status" = all status effects
	"moveDisable" = stops player from moving
	*/
	std::string effectType;
	int target;
	int user;

	Effect() {}
	Effect(std::string t, std::string dt, int targeted, int targeter, std::string act = "none", std::string e = "", double s = 0, int d = 0) {
		type = t;
		strength = s;
		durationType = dt;
		duration = d;
		actType = act;
		effectType = e;
		target = targeted;
		user = targeter;
	}
};

#endif