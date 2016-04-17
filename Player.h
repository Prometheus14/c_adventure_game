#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <list>

#include "Enemy.h"
#include "Item.h"

class Player {
private:
	std::string mName;
	int mMaxHealth;
	int mCurrentHealth;
	int mMoney;
	int mAttack;
	int mDefence;
	int mLevel;
	int mExp;
	int mExpRequired;
	bool isDead;

	std::list<Item> mItems;

public:
	std::string getName() { return mName; }
	int getHealth() { return mCurrentHealth; }
	int getMoney() { return mMoney; }
	int getDefence() { return mDefence; }	
	int getLevel() { return mLevel; }
	int getAttack() { return mAttack; }
	int getExp() { return mExp; }
	int getExpRequired() { return mExpRequired; }
	

	void setHealth(int amt) { mCurrentHealth = amt; }
	
	void showStats() {
		std::printf("\nPlayer %s: %dhp, $%d\n", mName.c_str(), mCurrentHealth, mMoney);
		printf("Current XP: %d.  Current Level: %d\n", mExp, mLevel);
	}

	void takeDamage(int damage);
	void regenHealth(int amount);
	void increaseMaxHealth(int amt);
	void increaseExp(int amt);
	void printInventory();
	bool canAffordItem(std::string name, int money);
	void addItem(Item newItem);
	bool removeItem(std::string name, Item &newItem);
	void addMoney(int money) { mMoney+=money; }
	void subtractMoney(int money) { mMoney -= money; }

	void levelUp();

	bool simulateBattle(std::vector<Enemy> &enemy);

	Player(std::string name);
	Player();


};