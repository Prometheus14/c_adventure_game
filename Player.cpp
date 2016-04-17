#pragma once
#include <random>
#include <ctime>

#include "Player.h"


Player::Player() {
	
	mName = "Lazy Bugger";
	mMaxHealth = 2000;
	mCurrentHealth = 2000;
	mMoney = 5000;
	mAttack = 100;
	mDefence = 100;
	mLevel = 1;
	mExp = 0;
	mExpRequired = 500;
	isDead = false;

	mItems.push_back(Item("Dagger",80,1));

}

Player::Player(std::string name)
{
	mName = name;
	mMaxHealth = 2000;
	mCurrentHealth = 2000;
	mMoney = 5000;
	mAttack = 100;
	mDefence = 100;
	mLevel = 1;
	mExp = 0;
	mExpRequired = 500;
	isDead = false;

	mItems.push_back(Item("Dagger", 80, 1));

}

void Player::takeDamage(int damage) {
	if (mCurrentHealth - damage <= 0) {
		mCurrentHealth = 0;
	}
	else { mCurrentHealth -= damage; }
}

void Player::regenHealth(int amount) {
	if (mCurrentHealth + amount >= mMaxHealth) {
		mCurrentHealth = mMaxHealth;
	}
	else {
		mCurrentHealth += amount;
	}
}

void Player::increaseMaxHealth(int amt) {
	mMaxHealth += amt;
}

void Player::increaseExp(int amt) {
	mExp += amt;
}

void Player::printInventory() {

	printf("*** %s's inventory ***\n\n",mName.c_str());
	printf("Money: %dGP\n\n",mMoney);

	std::list<Item>::iterator lit;

	int i = 0;

	for (lit = mItems.begin(); lit != mItems.end(); lit++) {
		printf("%d. %s x%d Price: %dGP\n", i, (*lit).getName().c_str(), (*lit).getCount(), (*lit).getValue());
		i++;
	}
}

bool Player::canAffordItem(std::string name, int money)
{
	std::list<Item>::iterator lit;

	for (lit = mItems.begin(); lit != mItems.end(); lit++) {
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

void Player::addItem(Item newItem)
{
	std::list<Item>::iterator lit;

	for (lit = mItems.begin(); lit != mItems.end(); lit++) {
		//if the item is already in the inventory, just increase the count
		if ((*lit).getName().c_str() == newItem.getName().c_str()) {
			(*lit).addOne();
			return;
		}
	}
	//if the item isnt in the inventory, add it
	mItems.push_back(newItem);
	mItems.back().setCount(1);
}

bool Player::removeItem(std::string name, Item & newItem)
{
	std::list<Item>::iterator lit;

	for (lit = mItems.begin(); lit != mItems.end(); lit++) {
		if ((*lit).getName() == name) {
			newItem = (*lit);
			(*lit).removeOne();
			if ((*lit).getCount() == 0) {
				mItems.erase(lit);
			}
			return true;
		}
	}
	return false;
}

void Player::levelUp() {
	printf("%s Leveled Up!\nLevel %d to Level %d\n", mName.c_str(), mLevel, mLevel + 1);
	mLevel++;
	mExp -= mExpRequired;
	mExpRequired += mExpRequired*0.5*(mLevel*0.1);
	mMaxHealth += 75;
	mCurrentHealth = mMaxHealth;
	mAttack += 15;
	showStats();
}

bool Player::simulateBattle(std::vector<Enemy> &enemy)
{
	//Setup and seed a random engine
	static std::mt19937 randomGenerator(time(nullptr));
	std::uniform_int_distribution<int> coinFlip(1,2);
	std::uniform_int_distribution<int> diceRoll(1, 6);
	
	//Random chance of who gets to start attacking first
	bool inBattle = true;
	int turn = 0;
	
	if (mCurrentHealth <= 0) {
		printf("%s is dead!\n\n", mName.c_str());
		inBattle = false;
	}
	else {

		printf("\nA fierce battle commences...\n\n");
	}
	turn = coinFlip(randomGenerator);
	while (inBattle) {

		switch (turn)
		{
		case 1:
			printf("%s attacks %s\t\t", mName.c_str(),enemy[0].getName().c_str());
			enemy[0].takeDamage(mAttack);
			if (enemy[0].getHealth() <= 0) {
				printf("%s is dead!\n\n", enemy[0].getName().c_str());
				enemy.erase(enemy.begin());
				//printf("Size of vector: %d\n\n", enemy.size());

				//check if enemy vector is empty
				if (enemy.size() == 0) {
					//printf("Size of vector: %d\n\n", enemy.size());
					int numEnemies = 100;
					for (int i = 0; i < numEnemies; i++) {
						enemy.push_back(Enemy());
						//printf("%d - %s added to Enemy army - attack %d\t\tSize of vector: %d\n", 
						//i+1, enemy[i].getName().c_str(),enemy[i].getAttack(),enemy.size());
					}
				}

				increaseExp(enemy[0].getExpGiven());
				//Check level up
				if (mExp >= mExpRequired) {
					levelUp();
				}
				inBattle = false;
			}
			else {
				printf("%s health: %d\n", enemy[0].getName().c_str(), enemy[0].getHealth());
				turn = 2;
			}
			break;
		case 2:
			printf("%s attacks %s\t\t", enemy[0].getName().c_str(),mName.c_str());
			takeDamage(enemy[0].getAttack());
			if (mCurrentHealth <= 0) {
				printf("%s is dead!\n\n", mName.c_str());
				inBattle = false;
				return true;
			}
			else {
				printf("%s health: %d\n", mName.c_str(), mCurrentHealth);
				turn = 1;
			}
			break;
		default:
			printf("Something went wrong\n\n");
			break;
		}

	}
	return false;
}

