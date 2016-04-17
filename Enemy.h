#pragma once
#include <string>
#include <iostream>
#include <conio.h>


class Enemy {
private:
	std::string mName;
	int mHealth;
	int mDefence;
	int mAttack;
	int mExpGiven;
	int mMoneyGiven;

public:
	Enemy();
	Enemy(std::string);
	int getHealth() { return mHealth; }
	int getExpGiven() { return mExpGiven; }
	int getMoneyGiven() { return mMoneyGiven; }
	std::string getName() { return mName; }
	int getAttack() { return mAttack; }
	int getDefence() { return mDefence; }
	
	void takeDamage(int d);
	void createArmy(int amt);


};