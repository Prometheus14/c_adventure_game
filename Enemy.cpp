#pragma once
#include <ctime>
#include <vector>
#include "Enemy.h"

Enemy::Enemy() {
	
	int randomIndex;
	std::string enemyNames[] = { "Troll","Dragon","Serpent","Goblin","Imp","Orc","Ogre", "Grumpy Hissing Duck", "Angry Flock of Geese" };
	int enemyAttack[] = { 150,200,180,300,150,120,200,650,600 };
	
	randomIndex = rand() % 9;

	mName = enemyNames[randomIndex];
	mHealth = enemyAttack[randomIndex];
	mDefence = enemyAttack[randomIndex];
	mAttack = enemyAttack[randomIndex];
	mExpGiven = enemyAttack[randomIndex];
	mMoneyGiven = mExpGiven * 2;
}

Enemy::Enemy(std::string name) {
	mName = name;
	mHealth = 200;
	mDefence = 200;
	mAttack = 200;
	mExpGiven = 100;
	mMoneyGiven = mExpGiven * 2;
}

void Enemy::takeDamage(int d) {
	if (mHealth - d <= 0) {
		mHealth = 0;
	}
	else { mHealth -= d; }
}

void Enemy::createArmy(int amt) {

	//Create a vector of enemies
	std::vector<Enemy> Enemies;

	int numEnemies = rand() % amt;
	for (int i = 0; i <= numEnemies; i++) {
		Enemies.push_back(Enemy());
		printf("%d - %s added to Enemy army\n", i, Enemies[i].getName().c_str());
	}

}
