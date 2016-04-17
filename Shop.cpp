#include "Shop.h"
#include <iostream>

Shop::Shop(std::string name, int money) {
	_name = name;
	_money = money;
}

void Shop::printShop() {
	printf("****Welcome to %s****\n\n", _name.c_str());
	printf("Money: %d GP\n\n", _money);
	std::list<Item>::iterator lit;

	int i = 0;

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		printf("%d. %s x%d Price: %dGP\n", i, (*lit).getName().c_str(), (*lit).getCount(),(*lit).getValue());
		i++;
	}
	printf("\n");

}

bool Shop::canAffordItem(std::string name, int money) {
	std::list<Item>::iterator lit;

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		if ((*lit).getName().c_str() == name) {
			if ((*lit).getValue() <= money) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool Shop::purchaseItem(std::string name, Item &newItem) {

	std::list<Item>::iterator lit;

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		if ((*lit).getName() == name) {
			newItem = (*lit);

			newItem.setCount(1);
			(*lit).removeOne();

			//if the item has a count of 0, we can remove it
			if ((*lit).getCount() == 0) {
				_items.erase(lit);
			}
			return true;
		}
	}
	return false;

}

void Shop::addItem(Item newItem)
{
	std::list<Item>::iterator lit;

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		//if the item is already in the shop, just increase count and return
		if ((*lit).getName() == newItem.getName()) {
			(*lit).addOne();
			return;
		}
	}

	//if the item isnt in the shop, add it to the shop
	_items.push_back(newItem);
	_items.back().setCount(1);
}