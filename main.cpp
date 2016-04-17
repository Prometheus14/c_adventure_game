#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <ctime>

#include "Player.h"
#include "Enemy.h"
#include "Shop.h"

void goDirection(std::string directions, Player &player, bool &isDead, std::vector<Enemy> &enemies);
void enterShop(Player &player, Shop &shop);

Shop myShop("Ducky's Shop", 2000);

int main() {

	myShop.addItem(Item("Leather Boots", 50, 3));
	myShop.addItem(Item("Leather Hat", 50, 3));
	myShop.addItem(Item("Leather Gloves", 50, 4));
	myShop.addItem(Item("Leather Gauntlets", 50, 3));
	myShop.addItem(Item("Leather Chestpiece", 100, 2));
	myShop.addItem(Item("Health Potion", 80, 20));

	bool isDead = false;
	srand(time(nullptr));
	int direction;

	enum eDirection {
		DIRECTION_NORTH = 1,
		DIRECTION_EAST,
		DIRECTION_SOUTH,
		DIRECTION_WEST
	};
	
	std::string name;

	printf("What is your name, Sir Knight? ");
	std::cin >> name;

	printf(std::string(50, '\n').c_str());
	printf(std::string(80, '*').c_str());
	printf("\n\n");
	

	Player player(name);

	//Create a vector of enemies
	std::vector<Enemy> Enemies;

	int numEnemies = 1;
	printf("The enemy is ammassing an army to attack!\n");
	for (int i = 0; i < numEnemies; i++) {
		Enemies.push_back(Enemy());
		//printf("%d - %s added to Enemy army - attack %d\n", i+1, Enemies[i].getName().c_str(),Enemies[i].getAttack());
	}

	
	printf("%s enters a magical world!\n",player.getName().c_str());


	while (!isDead) {

		printf("\nWhich way will you head? (or press '0' for inventory) \n");
		printf("\t1. North\n\t2. East\n\t3. South\n\t4. West\n\n");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cin >> direction;

		switch (direction)
		{
		case DIRECTION_NORTH:
			goDirection("North", player, isDead, Enemies);
			break;
		case DIRECTION_EAST:
			goDirection("East", player, isDead, Enemies);
			break;
		case DIRECTION_SOUTH:
			goDirection("South", player, isDead, Enemies);
			break;
		case DIRECTION_WEST:
			goDirection("West", player, isDead, Enemies);
			break;
		case 0:
			player.printInventory();
			break;
		default:
			printf("You wander down an unmarked path and meet your doom\n");
			isDead = true;
			break;
		}

	}

	std::cin.clear();
	std::cin.ignore(10000, '\n');
	char tmp;
	std::printf("\n\nPress any key to exit...");
	tmp = getchar();

	return 0;
}

void goDirection(std::string directions, Player &player, bool &isDead, std::vector<Enemy> &enemies) {
	
	//set up random chance for encounter
	static std::mt19937 randomGenerator(time(nullptr));
	std::uniform_int_distribution<int> diceRoll(1, 6);

	int chance = diceRoll(randomGenerator);
	int choice;
	int run;

	printf("You head %s\n",directions.c_str());
	if (chance > 4) {
		choice = 0;
		printf("You have encountered an enemy!\nWhat do you want to do?\n\n");
		printf("\t1. Fight\n\t2. Run!\n\n");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			isDead = player.simulateBattle(enemies);
			break;
		case 2:
			run = rand() % 10;
			if (run > 7) {
				printf("Sorry, you cant escape...\n\n");
				isDead = player.simulateBattle(enemies);
			}
			else {
				printf("You escaped!\n\n");
			}
			break;
		default:
			printf("Invalid entry...you must fight!\n\n");
			isDead = player.simulateBattle(enemies);
			break;
		}
	}
	else if (chance == 1) {
		choice = 0;
		printf("\nYou find a shop...will you enter?\n");
		printf("\t1. Enter\n\t2. Keep going\n");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			enterShop(player, myShop);
			break;
		default:
			break;
		}

	}
}

void enterShop(Player &player, Shop &shop)
{

	bool isDone = false;
	char input;
	std::string itemName;
	Item newItem("NOITEM", 0, 1);

	while (isDone == false) {
		shop.printShop();
		player.printInventory();

		printf("\nWould you like to buy or sell? Q to quit. (B/S): ");
		std::cin >> input;
		std::cin.ignore(64, '\n');
		std::cin.clear();

		//If the user types Q, leave the shop
		if (input == 'Q' || input == 'q') return;

		if (input == 'B' || input == 'b') { //buy
			printf("Enter the item you wish to buy: ");
			getline(std::cin, itemName);

			if (shop.canAffordItem(itemName, player.getMoney())) {

				if (shop.purchaseItem(itemName, newItem) == true) {
					player.addMoney(-newItem.getValue());
					player.addItem(newItem);
					shop.addMoney(newItem.getValue());
				}
				else {
					printf("That is an invalid item!\n");
					char tmp;
					std::printf("\n\nPress any key to continue...");
					tmp = getchar();
				}
			}
			else {
				printf("You don't have enough money!\n");
				char tmp;
				std::printf("\n\nPress any key to continue...");
				tmp = getchar();
			}

		}
		else { //sell
			printf("Enter the item you wish to sell: ");
			getline(std::cin, itemName);


			if (player.canAffordItem(itemName, shop.getMoney())) {

				if (player.removeItem(itemName, newItem) == true) {
					shop.addMoney(-newItem.getValue());
					shop.addItem(newItem);
					player.addMoney(newItem.getValue());
				}
				else {
					printf("That is an invalid item!\n");
					char tmp;
					std::printf("\n\nPress any key to continue...");
					tmp = getchar();
				}
			}
			else {
				printf("The shop doesn't have enough money!\n");
				char tmp;
				std::printf("\n\nPress any key to continue...");
				tmp = getchar();
			}
		}
	}
}