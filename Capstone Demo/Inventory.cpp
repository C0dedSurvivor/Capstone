#include "Inventory.h"

int Inventory::addItem(std::string name, int amt)
{
	int k;
	for (int f = 0; f < nOfItems; f++) {
		if (name.compare(items[f][0]) == 0) {
			if (items[f][1].compare("Medicine") == 0) {
				k = addItem(*new MedicineItem(name, amt));
			}
			else if (items[f][1].compare("Equippable") == 0) {
				for (int i = 0; i < amt; i++) {
					k = addItem(*new Equippable(name));
				}
			}
			else if (items[f][1].compare("Basic") == 0) {
				k = addItem(*new Item(name, amt), "");
			}
		}
	}
	printInv();
	return k;
}

int Inventory::addItem(MedicineItem i)
{
	for (int f = 0; f < nOfItems; f++) {
		if (i.name.compare(items[f][0]) == 0) {
			bool flag = false;
			for (int d = 0; d < medInv.size(); d++) {
				if (i.name.compare(medInv.at(d).name) == 0) {
					flag = true;
					if (i.amt + medInv.at(d).amt <= std::stoi(items[f][2])) {
						medInv.at(d).amt += i.amt;
					}
					else {
						i.amt = std::stoi(items[f][2]) - medInv.at(d).amt;
						medInv.at(d).amt += i.amt;
					}
				}
			}
			if (!flag) {
				if (i.amt > std::stoi(items[f][2]))
					i.amt = std::stoi(items[f][2]);
				medInv.emplace_back(i);
			}
		}
	}
	printInv();
	return i.amt;
}

int Inventory::addItem(Discs d)
{
	discInv.emplace_back(d);
	printInv();
	return 1;
}

int Inventory::addItem(Equippable e)
{
	equipInv.emplace_back(e);
	printInv();
	return 1;
}

int Inventory::addItem(Item i, std::string s)
{
	for (int f = 0; f < nOfItems; f++) {
		if (i.name.compare(items[f][0]) == 0) {
			bool flag = false;
			for (int d = 0; d < basicInv.size(); d++) {
				if (i.name.compare(basicInv.at(d).name) == 0) {
					flag = true;
					if (i.amt + basicInv.at(d).amt <= std::stoi(items[f][2])) {
						basicInv.at(d).amt += i.amt;
					}
					else {
						i.amt = std::stoi(items[f][2]) - basicInv.at(d).amt;
						basicInv.at(d).amt += i.amt;
					}
				}
			}
			if (!flag) {
				if (i.amt > std::stoi(items[f][2]))
					i.amt = std::stoi(items[f][2]);
				basicInv.emplace_back(i);
			}
		}
	}
	printInv();
	return i.amt;
}

bool Inventory::removeItem(int place, std::string itemType, int amt)
{
	//haven't modified med part
	if (itemType.compare("Medicine") == 0) {
		if (medInv.at(place).amt - amt > 0) {
			medInv.at(place).amt -= amt;
		}
		else {
			medInv.erase(medInv.begin() + place);
		}
		return true;
	}
	else if (itemType.compare("Disc") == 0) {
		discInv.erase(discInv.begin() + place);
		return true;
	}else if (itemType.compare("Equippable") == 0) {
		equipInv.erase(equipInv.begin() + place);
		return true;
	}
	return false;
}

bool Inventory::removeItem(std::string name, int amt)
{
	for (int f = 0; f < nOfItems; f++) {
		if (name.compare(items[f][0]) == 0) {
			if (items[f][1].compare("Medicine") == 0) {
				bool flag = false;
				for (int d = 0; d < medInv.size(); d++) {
					if (items[f][0].compare(medInv.at(d).name) == 0) {
						flag = true;
						if (amt + medInv.at(d).amt <= std::stoi(items[f][2])) {
							medInv.at(d).amt += amt;
						}
						else {
							amt = std::stoi(items[f][2]) - medInv.at(d).amt;
							medInv.at(d).amt += amt;
						}
					}
				}
				if (!flag) {
					medInv.emplace_back(*new MedicineItem(name, amt));
				}
			}
			else if (items[f][1].compare("Equippable") == 0) {
				for (int i = 0; i < amt; i++) {
					equipInv.emplace_back(*new Equippable(name));
				}
			}

		}
	}
	return false;
}

void Inventory::printInv()
{
	std::cout << "Printing Inventory:" << std::endl;
	for (int i = 0; i < basicInv.size(); i++) {
		std::cout << "Basic Item " << i << ": " << basicInv.at(i).name << " of amount " << basicInv.at(i).amt << std::endl;
	}
	for (int i = 0; i < medInv.size(); i++) {
		std::cout << "Medicine Item " << i << ": " << medInv.at(i).name << " of amount " << medInv.at(i).amt << std::endl;
	}
	for (int i = 0; i < equipInv.size(); i++) {
		std::cout << "Equippable Item " << i << ": " << equipInv.at(i).name << " of amount " << equipInv.at(i).amt << std::endl;
	}
	std::cout << std::endl << std::endl;
}
