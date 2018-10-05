#ifndef STATCHANGE_H
#define STATCHANGE_H
class statChange {
public:
	//stat it affects (1=pAtk, 2=mAtk, 3=pDef, 4=Mdef, 5=Speed, 6=Accuracy)
	int stat;

	/*
	* Strength of the buff / debuff:
	* < 1 for debuff (int decimal)
	* < 5 for buff (in decimal - 1)
	* 6 to remove the current stat change for that stat
	* 7 to reverse the current stat change (debuff to buff, buff to debuff of the same strength)
	*/
	double strength;

	//chance of it happening(in decimal)
	double chance;

	statChange() {
		stat = 1;
		strength = 1;
		chance = 1;
	}
	statChange(int s, double str, double c) {
		stat = s;
		strength = str;
		chance = c;
	}
};
#endif