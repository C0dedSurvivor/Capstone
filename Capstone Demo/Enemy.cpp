#include "Enemy.h"

const std::string monsterList[monsters][7] = { {"slime", "30", "30", "30", "30", "60", "250"},
											 { "slime2", "30", "30", "30", "30", "60", "250" },
											 { "skeleton", "60", "40", "10", "40", "60", "200" },
											 { "golem", "70", "30", "80", "20", "40", "400" },
											 { "mainBossKun", "100", "100", "100", "100", "100", "800" } };

void Enemy::ITSALIVE(){
	for (int i = 0; i < monsters; i++) {
		if (monsterList[i][0].compare(name) == 0) {
			double aMod = 1;
			double dMod = 1;
			if (variant == 1) {
				aMod = 0.75;
				dMod = 1.25;
			}
			else {
				aMod = 1.25;
				dMod = 0.75;
			}
			pAtk = rand() % 30 + stoi(monsterList[i][1]) * level * aMod;
			mAtk = rand() % 30 + stoi(monsterList[i][2]) * level * aMod;
			pDef = rand() % 30 + stoi(monsterList[i][3]) * level * dMod;
			mDef = rand() % 30 + stoi(monsterList[i][4]) * level * dMod;
			speed = rand() % 50 + stoi(monsterList[i][5]) * level * aMod;
			//maxHealth = std::shared_ptr<int>(new int(rand() % 70 + stoi(monsterList[i][6]) * level * aMod));
			maxHealth = std::shared_ptr<int>(new int(2));
			curHealth = std::shared_ptr<int>(new int(*maxHealth));
			std::cout << pAtk << ", " << pDef << ", " << mAtk << ", " << mDef << ", " << speed << std::endl;
			break;
		}
	}
}

void Enemy::die(){
}