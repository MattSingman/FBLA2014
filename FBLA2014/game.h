#include <vector>

#ifndef GAME_H
#define GAME_H

class game {

	int money = 100000; //starting money
	int computerHP = 100;

	int wave = 0;



public:
	game() {};

	int getMoney() const { return money; };
	void subtractMoney(int);
	void addMoney(int);

	int getHP() const { return computerHP; };
	void giveDamage(int);


};
#endif