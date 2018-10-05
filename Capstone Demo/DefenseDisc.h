#ifndef DEFENSEDISC_H
#define DEFENSEDISC_H

class DefenseDisc : public Discs {
public:
	/*
	* > 0 & < 1 for % max health heal (in decimal) (caps at 75%)
	* > -1 & <= 0 for % current health heal (in decimal + 1) (caps at 100%)
	* > -2 & < -1 for % missing health heal (in decimal + 2) (caps at 75%)
	* any other number is a flat heal value
	*/
	double healStrength;

	/*
	* > 0 & < 1 for % max health shield (in decimal) (caps at 100%)
	* > -2 & < 0 for % current health shield (in decimal + 2) (caps at 125%)
	* > -4 & < -2 for % missing health shield (in decimal + 4) (caps at 200%)
	* any other number is a flat shield value
	*/
	double shieldStrength;

	DefenseDisc() {};

	DefenseDisc(std::string name, int rom, int ram, double shield = 0, double heal = 0, std::vector<statChange> stat = {}) {
		nickname = name;
		discName = name;
		discType = 3;
		ramUse = ram;
		romUse = rom;
		shieldStrength = shield;
		healStrength = heal;
		statChanges = stat;
	}

	DefenseDisc combine(DefenseDisc d2, double combLevel) {
		DefenseDisc d;
		d.discName = nickname;
		d.nickname = nickname;
		d.discType = 3;
		d.ramUse = (ramUse + d2.ramUse) * combLevel;
		d.romUse = (romUse + d2.romUse) * combLevel;

		if (healStrength > 1) 
		{
			if (d2.healStrength > 1) // flat heal value
				d.healStrength = (int)((healStrength + d2.healStrength) * combLevel);
			else if (d2.healStrength > 0)
				d.healStrength = (int)((healStrength * (d2.healStrength + 1)) * combLevel);
			else if (d2.healStrength > -1)
				d.healStrength = (int)((healStrength * (d2.healStrength + 1.9)) * combLevel);
			else //d2.healStrength > -2
				d.healStrength = (int)((healStrength * (d2.healStrength + 2.9)) * combLevel);
		}
		else if (healStrength > 0) // % max health
		{
			if (d2.healStrength > 1)
				d.healStrength = (int)((healStrength + (d2.healStrength / 10)) * combLevel * 100) / 100;
			else if (d2.healStrength > 0)
				d.healStrength = (int)((healStrength + d2.healStrength) * 0.8 * combLevel * 100) / 100;
			else if (d2.healStrength > -1)
				d.healStrength = (int)((healStrength + ((d2.healStrength + 1) / 1.3) - 0.02) * combLevel * 100) / 100;
			else //d2.healStrength > -2
				d.healStrength = (int)((healStrength + ((d2.healStrength + 2) / 1.3) - 0.02) * combLevel * 100) / 100;
			if (d.healStrength > 0.75)
				d.healStrength = 0.75;
		}
		else if (healStrength > -1) // % current health
		{
			if (d2.healStrength > 1)
				d.healStrength = (int)((healStrength + 1 + (d2.healStrength / 10)) * combLevel * 100) / 100;
			else if (d2.healStrength > 0)
				d.healStrength = (int)((healStrength + 1 + d2.healStrength * 1.1) * combLevel * 100) / 100;
			else if (d2.healStrength > -1)
				d.healStrength = (int)(((healStrength + 1) + (d2.healStrength + 1) - 0.02) * combLevel * 100) / 100;
			else //d2.healStrength > -2
				d.healStrength = (int)(((healStrength + 1) + (d2.healStrength + 2) - 0.02) * combLevel * 100) / 100;
			if (d.healStrength > 0)
				d.healStrength = 0;
		}/////////////////////////
		else if (healStrength > -2) // % missing health
		{
			if (d2.healStrength > 1)
				d.healStrength = (int)((healStrength + 2 + (d2.healStrength / 10)) * combLevel * 100) / 100;
			else if (d2.healStrength > 0)
				d.healStrength = (int)((healStrength + 2 + d2.healStrength * 1.1) * combLevel * 100) / 100;
			else if (d2.healStrength > -1)
				d.healStrength = (int)(((healStrength + 2) + (d2.healStrength + 1) - 0.02) * combLevel * 100) / 100;
			else //d2.healStrength > -2
				d.healStrength = (int)(((healStrength + 2) + (d2.healStrength + 2) - 0.02) * combLevel * 100) / 100;
			if (d.healStrength > -1.25)
				d.healStrength = -1.25;
		}
	}
};

#endif