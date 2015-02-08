#ifndef GAME_H
#define GAME_H

class game {

	int money = 1000; //starting money

public:
	game() {};

	int getMoney() const { return money; };
	void subtractMoney(int);
	void addMoney(int);
};
#endif