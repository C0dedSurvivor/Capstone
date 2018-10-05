#ifndef MITEM_H
#define MITEM_H

#include <string>
#include "Item.h"

class MedicineItem : public Item {
public:

	MedicineItem(std::string n, int a) {
		name = n;
		amt = a;
	}
};

#endif