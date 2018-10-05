#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <string>
#include "Chest.h"
#include "Door.h"
#include "Stairs.h"
#include "EncounterSpace.h"
#include "NPC.h"
#include "BattleTrigger.h"

class Map {
public:
	int map[20][20];
	bool collision[20][20];
	std::vector<Chest> chestList;
	std::vector<Door> doorList;
	std::vector<Stairs> stairList;
	std::vector<sf::Vector2f> startList;
	std::vector<EncounterSpace> encounters;
	std::vector<NPC> npcList;
	std::vector<BattleTrigger> bTriggers;
	
	Map();
	~Map();
	void addPlayerStart(int x, int y);
	void addWall(int x, int y);
	//length is wall length, including corners
	void addHollowWallRect(int x, int y, int xL, int yL);
	//d is direction, 'V' for vertical, 'H' for horizontal, l is length including starting coord
	void addWallLine(int x, int y, char d, int l);
	void addFloor(int x, int y);
	//length is wall length, including corners
	void addHollowFloorRect(int x, int y, int xL, int yL);
	//length is wall length, including corners
	void addFilledFloorRect(int x, int y, int xL, int yL);
	//d is direction, 'V' for vertical, 'H' for horizontal, l is length including starting coord
	void addFloorLine(int x, int y, char d, int l);
	void addStairs(int x, int y, char d, int m, int sX, int sY);
	void addDoor(int x, int y, char d);
	void addChest(int x, int y);
	void addChest(int x, int y, std::vector<Item> i);
	void addEncounterSpace(int x, int y, int xL, int yL, std::string area, int level);
	void addNPC(int x, int y, std::string n, std::vector<std::pair<std::string, std::string>> s);
	void addBattleTrigger(int x, int y, std::string specCond);
	void addBattleTriggerWText(int x, int y, std::string specCond, std::vector<std::pair<std::string, std::string>> s);
	void addOther(int x, int y, int n);
	void addOther(int x, int y, int n, bool collide);
};

#endif