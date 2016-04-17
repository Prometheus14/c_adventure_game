#include "Item.h"

//item constructor
Item::Item(std::string name, int value, int count)
{
	_name = name;
	_value = value;
	_count = count;
}

//adds an item
void Item::addOne()
{
	_count++;
}

//removes an item
void Item::removeOne()
{
	if (_count > 0) {
		_count--;
	}
}