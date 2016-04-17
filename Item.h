#pragma once
#include <string>

class Item {
private:
	std::string _name;
	int _value;
	int _count;

public:

	Item(std::string name, int value, int count);

	void addOne();
	void removeOne();

	std::string getName() { return _name; }
	int getValue() { return _value; }
	int getCount() { return _count; }

	void setCount(int count) { _count = count; }

};