#ifndef INV_H
#define INV_H

#include <vector>
#include <memory>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Item.h"
#include "Equippable.h"
#include "MedicineItem.h"
#include "Disc.h"

const int nOfItems = 8;
//name, type, max stack size, can throw away
const std::string items[nOfItems][4] = { { "Arrow", "Basic", "99", "true" }, 
	{ "Sword", "Equippable", "1", "true" }, 
	{ "Health Potion", "Medicine", "20", "true" }, 
	{ "Dragon Scale", "Basic", "100", "true" }, 
	{ "Eternal Flame", "Basic", "100", "true" }, 
	{ "Bones", "Basic", "100", "true" }, 
	{ "Quartz", "Basic", "100", "true" }, 
	{ "Werewolf Fangs", "Basic", "100", "true" } };

class Inventory {
public:
	std::vector<MedicineItem> medInv;
	std::vector<Discs> discInv;
	std::vector<Equippable> equipInv;
	std::vector<Item> basicInv;

	Inventory() {}
	int addItem(std::string name, int amt);
	int addItem(MedicineItem i);
	int addItem(Discs d);
	int addItem(Equippable e);
	int addItem(Item i, std::string s);
	bool removeItem(int place, std::string itemType, int amt);
	bool removeItem(std::string name, int amt);
	void printInv();
};

#endif