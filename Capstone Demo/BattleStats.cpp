#include "BattleStats.h"

void BattleStats::reset(){
	pAtkMod = 1.0;
	mAtkMod = 1.0;
	pDefMod = 1.0;
	mDefMod = 1.0;
	accMod = 1.0;
}

int BattleStats::heal(double h){
	int healAmount = 0;
	if (h < 1 && h > 0) {
		*curHealth += (*maxHealth * h);
		healAmount = *maxHealth * h;
	}else if (h > 1 && h < 2){
		*curHealth = *maxHealth;
		healAmount = *maxHealth - *curHealth;
	}else {
		*curHealth += h;
		healAmount = h;
	}
	if (*curHealth > *maxHealth) {
		healAmount -= (*curHealth - *maxHealth);
		*curHealth = *maxHealth;
	}
	return healAmount;
}

std::pair<int, int> BattleStats::takeDamage(double d){
	int damageAmount = d;
	int shieldDamage = 0;
	if (shield > 0) {
		if (shield > d) {
			shield -= d;
			shieldDamage += d;
			damageAmount = 0;
		}
		else {
			shieldDamage += shield;
			damageAmount -= shield;
			shield = 0;
		}
	}
	else {
		*curHealth -= d;
	}
	if (*curHealth <= 0) {
		damageAmount -= (0 - *curHealth);
		*curHealth = 0;
		isAlive = false;
	}
	
	return std::pair<int, int>(shieldDamage, damageAmount);
}

//When sending the amount make sure it is already multiplied by the disc affinity mod
std::string BattleStats::statBuff(int stat, double amount, double chance)
{
	
	if ((rand() % 100) + 1 <= chance * 100) {
		std::string modded;
		if (stat == 1) {
			pAtkMod *= amount;
			modded = "Physical Attack";
		}
		else if (stat == 2) {
			mAtkMod *= amount;
			modded = "Magical Attack";
		}
		else if (stat == 3) {
			pDefMod *= amount;
			modded = "Physical Defense";
		}
		else if (stat == 4) {
			mDefMod *= amount;
			modded = "Magical Defense";
		}
		else if (stat == 5) {
			speedMod *= amount;
			modded = "Speed";
		}
		else if (stat == 6) {
			accMod *= amount;
			modded = "Accuracy";
		}
		if (amount > 1)
			return name + "'s " + modded + " was increased!";
		else
			return name + "'s " + modded + " was decreased!";
	}
	else {
		return "";
	}
}
