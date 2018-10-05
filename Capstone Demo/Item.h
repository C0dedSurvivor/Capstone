#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
	std::string name;
	int amt;
	Item() {

	}
	Item(std::string n, int a) {
		name = n;
		amt = a;
	}

	void add(int a) {
		amt += a;
	}
	void remove(int a) {
		amt -= a;
	}
};

#endif