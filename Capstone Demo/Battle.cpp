#include "Battle.h"

void Battle::start()
{
	battleState = "start";
	//nOfEnemies = 4;
	playerChoosesMoves();
}

void Battle::battle()
{
	setTurnOrder();
}

void Battle::end(std::string t)
{
	battleState = "end";
	if (t.compare("player") == 0) {

	}
	if (t.compare("enemy") == 0) {
		int exp = 0;
		for (int i = nOfPlayers; i < nOfPlayers + nOfEnemies; i++) {
			if (pawns.at(i)->name.compare("slime") || pawns.at(i)->name.compare("slime2"))
				exp += 100;
			else if (pawns.at(i)->name.compare("skeleton"))
				exp += 150;
			else if (pawns.at(i)->name.compare("golem"))
				exp += 150;
			else if (pawns.at(i)->name.compare("mainBossKun"))
				exp += 500;
		}
		for (int i = 0; i < nOfPlayers; i++) {
			dynamic_cast<Player*>(pawns.at(i).get())->gainEXP(exp);
		}
	}
	music.stop();
}

void Battle::generateEnemies(int eCount) {
	for (int i = 0; i < eCount; i++) {
		Enemy e;
		pawns.emplace_back(std::make_shared<Enemy>(e));
	}
	genedPawns = true;
}

void Battle::generateEnemies(std::string specBattleCond)
{
	Enemy e;
	e = Enemy("skeleton", 1, 0);
	pawns.emplace_back(std::make_shared<Enemy>(e));
	e = Enemy("mainBossKun", 2, 0);
	pawns.emplace_back(std::make_shared<Enemy>(e));
	e = Enemy("skeleton", 1, 0);
	pawns.emplace_back(std::make_shared<Enemy>(e));
	convList.emplace_back(std::make_pair<std::string, int>("Boss-Kun: Hello idiot human", 1));
	convList.emplace_back(std::make_pair<std::string, int>("Player 1: Screw you", 1));
	convList.emplace_back(std::make_pair<std::string, int>("Boss-Kun: Ow", 2));
	genedPawns = true;
}

void Battle::playerChoosesMoves() {
	battleState = "playerMoves";
	cont = false;
	playersChosen = false;
	bool done = false;
	do{
		done = true;
		for (int i = 0; i < nOfPlayers; i++) {
			if (!pawns.at(i)->enteredMove)
				done = false;
		}
		playersChosen = done;
	} while (!cont);
	enemiesChooseMoves();
}

void Battle::enemiesChooseMoves() {
	battleState = "enemyMoves";
	cont = false;
	playersChosen = false;
	for (int i = nOfPlayers; i < nOfPlayers + nOfEnemies; i++) {
		moveInputList.emplace_back(std::unique_ptr<BattleMove>(new BattleMove("basic", i, rand() % nOfPlayers)));
	}
	setTurnOrder();
}

void Battle::setTurnOrder() {
	for (int i = 0; i < moveInputList.size() - 1; i++) {
		int lowest = i;
		for (int j = i + 1; j < moveInputList.size(); j++) {
			if (pawns.at(moveInputList.at(j)->user)->speed * pawns.at(moveInputList.at(j)->user)->speedMod < pawns.at(moveInputList.at(lowest)->user)->speed * pawns.at(moveInputList.at(lowest)->user)->speedMod)
				lowest = j;
		}
		if(i != lowest)
			std::swap(moveInputList.at(i), moveInputList.at(lowest));
	}
	makeMoves();
}

void Battle::enterMoveType(int i)
{
	//1 = basic attack
	moveSelected = i;
	//21 through 24 = disc
}

void Battle::targetEnemy(int i)
{
	selectedEnemy = i;
	bool flag = false;
	for (int i = 0; i < moveInputList.size(); i++) {
		if (moveInputList.at(i)->user == selectedPlayer) {
			flag = true;
			if (moveSelected == 1)
				moveInputList.insert(moveInputList.begin() + i, std::unique_ptr<BattleMove>(new BattleMove("basic", selectedPlayer, selectedEnemy + nOfPlayers)));
			else if (moveSelected > 20 && moveSelected < 25)
				moveInputList.insert(moveInputList.begin() + i, std::unique_ptr<BattleMove>(new BattleMove("disc " + (moveSelected - 20), selectedPlayer, selectedEnemy + nOfPlayers)));
			moveInputList.erase(moveInputList.begin() + i + 1);
			break;
		}
	}
	if (!flag) {
		if(moveSelected == 1)
			moveInputList.emplace_back(std::unique_ptr<BattleMove>(new BattleMove("basic", selectedPlayer, selectedEnemy + nOfPlayers)));
		else if (moveSelected > 20 && moveSelected < 25)
			moveInputList.emplace_back(std::unique_ptr<BattleMove>(new BattleMove("disc " + std::to_string(moveSelected - 20), selectedPlayer, selectedEnemy + nOfPlayers)));
	}
	pawns.at(selectedPlayer)->enteredMove = true;
	// test string outputter
	for (int i = 0; i < moveInputList.size(); i++) {
		std::cout << moveInputList.at(i)->user << " using " << moveInputList.at(i)->moveType << " on ";
		for (int j = 0; j < 8; j++) {
			std::cout << std::boolalpha << moveInputList.at(i)->target[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	selectedPlayer = -1;
	moveSelected = -1;
	selectedEnemy = -1;
}

void Battle::makeMoves() {
	battleState = "genMoves";
	for (int i = 0; i < moveInputList.size(); i++) {
		if (moveInputList.at(i)->moveType.compare("basic") == 0) {
			Move m(moveInputList.at(i)->user, moveInputList.at(i)->target);
			m.generateMove(pawns);
			moveExecutableList.emplace_back(std::make_unique<Move>(m));
		}
		else if (moveInputList.at(i)->moveType.find("disc") != -1) {
			Move m(moveInputList.at(i)->user, moveInputList.at(i)->target);
			BattleStats* user = pawns.at(moveInputList.at(i)->user).get();
			Discs* disc = dynamic_cast<Player*>(user)->equippedDiscs.at(std::stoi(moveInputList.at(i)->moveType.substr(5, 6))).get();
			if(dynamic_cast<Player*>(user)->equippedDiscs.at(std::stoi(moveInputList.at(i)->moveType.substr(5, 6)))->discType == 1)
				m.generateMove(pawns, *dynamic_cast<AttackDisc*>(disc));
			if (dynamic_cast<Player*>(user)->equippedDiscs.at(std::stoi(moveInputList.at(i)->moveType.substr(5, 6)))->discType == 2)
				m.generateMove(pawns, *dynamic_cast<MagicDisc*>(disc));
			if (dynamic_cast<Player*>(user)->equippedDiscs.at(std::stoi(moveInputList.at(i)->moveType.substr(5, 6)))->discType == 3)
				m.generateMove(pawns, *dynamic_cast<DefenseDisc*>(disc));
			moveExecutableList.emplace_back(std::make_unique<Move>(m));
		}
	}
	moveInputList.clear();
	executeMoves();
}

void Battle::executeMoves()
{
	bool playersFucked = true;
	bool enemiesFucked = true;
	int j = moveExecutableList.size();
	for (int i = 0; i < j; i++) {
		if (pawns.at(moveExecutableList.at(0)->user)->isAlive) {
			std::cout << std::to_string(moveExecutableList.at(0)->initialDamage) << std::endl;
			for (int k = 0; k < 8; k++) {
				if (moveExecutableList.at(0)->target[k] && pawns.at(k)->isAlive) {
					if(moveExecutableList.at(0)->user >= nOfPlayers)
						textPass = "The enemy " + pawns.at(moveExecutableList.at(0)->user)->name + " attacks " + pawns.at(k)->name ;
					else {
						if(moveExecutableList.at(0)->type.compare("Basic") == 0)
							textPass = pawns.at(moveExecutableList.at(0)->user)->name + " attacks the enemy " + pawns.at(k)->name;
						else
							textPass = pawns.at(moveExecutableList.at(0)->user)->name + " uses " + moveExecutableList.at(0)->type + " the enemy " + pawns.at(k)->name;
					}
					while (textPass.compare("") != 0) {}
					pawns.at(k)->takeDamage(moveExecutableList.at(0)->initialDamage);
					if (k >= nOfPlayers)
						textPass = "The enemy " + pawns.at(k)->name + " takes " + std::to_string(moveExecutableList.at(0)->initialDamage) + " damage";
					else
						textPass = pawns.at(k)->name + " takes " + std::to_string(moveExecutableList.at(0)->initialDamage) + " damage";
					while (textPass.compare("") != 0) {}
				}
			}
			moveExecutableList.erase(moveExecutableList.begin());
			playersFucked = true;
			for (int i = 0; i < nOfPlayers; i++) {
				if (pawns.at(i)->isAlive) {
					playersFucked = false;
					break;
				}
			}
			enemiesFucked = true;
			for (int i = nOfPlayers; i < nOfPlayers + nOfEnemies; i++) {
				if (pawns.at(i)->isAlive) {
					enemiesFucked = false;
					break;
				}
			}
		}
		else {
			moveExecutableList.erase(moveExecutableList.begin());
		}
	}

	for (int i = 0; i < pawns.size(); i++) {
		pawns.at(i)->enteredMove = false;
		std::cout << "char" << std::to_string(i) << ": Health " << std::to_string(*(pawns.at(i)->curHealth)) << "/" << std::to_string(*(pawns.at(i)->maxHealth)) << "  Alive = " << std::boolalpha << pawns.at(i)->isAlive << std::endl;
	}

	if (convList.size() > 0)
		while (convList.at(0).second == 1) {
			textPass = convList.at(0).first;
			while (textPass.compare("") != 0) {}
			convList.erase(convList.begin());
			if (convList.size() == 0)
				break;
		}
	for (int i = 0; i < convList.size(); i++) {
		convList.at(i).second--;
	}
	if (playersFucked)
		end("player");
	else if (enemiesFucked)
		end("enemy");
	else
		playerChoosesMoves();
}

void Battle::continueChoice(int i)
{
	cont = true;
}
