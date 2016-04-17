#pragma once
#include <string>
#include <list>

#include "Item.h"

class Shop {
public:
	Shop(std::string name, int money);

	void printShop();
	bool canAffordItem(std::string name, int money);
	bool purchaseItem(std::string name, Item &newItem);
	void addItem(Item newItem);

	void addMoney(int money) { _money += money; }

	std::string getName() { return _name; }
	int getMoney() { return _money; }

private:
	std::string _name;
	int _money;
	std::list<Item> _items;

};