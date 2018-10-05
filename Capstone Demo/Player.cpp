#include "Player.h"

void Player::genRandomPlayer() {
	name = "Player Test";
	pAtk = rand() % 30 + 90;
	mAtk = rand() % 30 + 90;
	pDef = rand() % 30 + 90;
	mDef = rand() % 30 + 90;
	speed = rand() % 50 + 120;
	maxHealth = std::shared_ptr<int>(new int(rand() % 70 + 325));
	curHealth = std::shared_ptr<int>(new int(*maxHealth));
	maxRam = rand() % 50 + 120;
	curRam = maxRam;
	maxRom = rand() % 50 + 120;
	curRom = maxRom;
	level = 1;
	exp = 0;
	std::cout << pAtk << ", " << pDef << ", " << mAtk << ", " << mDef << ", " << speed << std::endl;
}

void Player::gainEXP(int expGain)
{
	exp += expGain;
	if(exp >= expPerLevel()){
		exp -= expPerLevel();
		level++;
		pAtk += rand() % 5 + 5;
		mAtk += rand() % 5 + 5;
		pDef += rand() % 5 + 5;
		mDef += rand() % 5 + 5;
		speed += rand() % 10 + 10;
		int healthGain = rand() % 10 + 30;
		*maxHealth += healthGain;
		*curHealth += healthGain;
		gainEXP(0);
	}
}

int Player::expPerLevel()
{
	return 19 + level * level;
}
