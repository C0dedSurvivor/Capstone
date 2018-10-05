#include "Map.h"

Map::Map()
{
	//floor = 1, wall = 2, stairs = 3; chest = 4; door = 5-8; NPC = 9;
	//10-11 = lamp on desk against wall; 12 = desk; 13-15 = wall torch (front, left, right)
	//16-17 = bed
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			collision[i][j] = false;
			map[i][j] = 0;
		}
	}
}

Map::~Map()
{
}

void Map::addPlayerStart(int x, int y)
{
	startList.emplace_back(sf::Vector2f(x, y));
}

void Map::addWall(int x, int y)
{
	map[x][y] = 2;
	collision[x][y] = true;
}

void Map::addHollowWallRect(int x, int y, int xL, int yL)
{
	for (int i = x; i < xL + x; i++) {
		map[i][y] = 2;
		collision[i][y] = true;
		map[i][y + yL - 1] = 2;
		collision[i][y + yL - 1] = true;
	}
	for (int i = y + 1; i < yL + y - 1; i++) {
		map[x][i] = 2;
		collision[x][i] = true;
		map[x + xL - 1][i] = 2;
		collision[x + xL - 1][i] = true;
	}
}

void Map::addWallLine(int x, int y, char d, int l)
{
	for (int i = 0; i < l; i++) {
		if (d == 'V'){
			map[x][y + i] = 2;
			collision[x][y + i] = true;
		}
		else {
			map[x + i][y] = 2;
			collision[x + i][y] = true;
		}
	}
}

void Map::addFloor(int x, int y)
{
	map[x][y] = 1;
	collision[x][y] = false;
}

void Map::addHollowFloorRect(int x, int y, int xL, int yL)
{
	for (int i = x; i < xL + x; i++) {
		map[i][y] = 1;
		collision[i][y] = false;
		map[i][y + yL - 1] = 1;
		collision[i][y + yL - 1] = false;
	}
	for (int i = y + 1; i < yL + y - 1; i++) {
		map[x][i] = 1;
		collision[x][i] = false;
		map[x + xL - 1][i] = 1;
		collision[x + xL - 1][i] = false;
	}
}

void Map::addFilledFloorRect(int x, int y, int xL, int yL)
{
	for (int i = x; i < xL + x; i++) {
		for (int j = y; j < yL + y; j++) {
			map[i][j] = 1;
			collision[i][j] = false;
		}
	}
}

void Map::addFloorLine(int x, int y, char d, int l)
{
	for (int i = 0; i < l; i++) {
		if (d == 'V') {
			map[x][y + i] = 1;
			collision[x][y + i] = false;
		}
		else {
			map[x + i][y] = 1;
			collision[x + i][y] = false;
		}
	}
}

void Map::addStairs(int x, int y, char d, int m, int sX, int sY)
{
	startList.emplace_back(sf::Vector2f(sX, sY));
	stairList.emplace_back(Stairs(x, y, d, m, startList.size() - 1));
	map[x][y] = 3;
	collision[x][y] = true;
}

void Map::addDoor(int x, int y, char d)
{
	doorList.emplace_back(Door(x, y, d));
	if(d == 'V')
		map[x][y] = 5;
	if (d == 'H')
		map[x][y] = 7;
	collision[x][y] = true;
}

void Map::addChest(int x, int y)
{
	chestList.emplace_back(Chest(x, y));
	map[x][y] = 4;
	collision[x][y] = true;
}

void Map::addChest(int x, int y, std::vector<Item> i)
{
	chestList.emplace_back(Chest(x, y, i));
	map[x][y] = 4;
	collision[x][y] = true;
}

void Map::addEncounterSpace(int x, int y, int xL, int yL, std::string area, int level)
{
	encounters.emplace_back(EncounterSpace(x * 16, y * 16, xL * 16, yL * 16, area, level));
}

void Map::addNPC(int x, int y, std::string n, std::vector<std::pair<std::string, std::string>> s)
{
	npcList.emplace_back(NPC(x, y, n, s));
	map[x][y] = 9;
	collision[x][y] = true;
}

void Map::addBattleTrigger(int x, int y, std::string specCond)
{
	bTriggers.emplace_back(BattleTrigger(x, y, specCond));
	map[x][y] = 9;
	collision[x][y] = true;
}

void Map::addBattleTriggerWText(int x, int y, std::string specCond, std::vector<std::pair<std::string, std::string>> s)
{
	npcList.emplace_back(NPC(x, y, s));
	bTriggers.emplace_back(BattleTrigger(x, y, specCond));
	map[x][y] = 9;
	collision[x][y] = true;
}

void Map::addOther(int x, int y, int n)
{
	map[x][y] = n;
}

void Map::addOther(int x, int y, int n, bool collide)
{
	map[x][y] = n;
	collision[x][y] = collide;
}
