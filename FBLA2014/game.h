#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "MessageBox.h"

#ifndef GAME_H
#define GAME_H

class game {

	int money = 10000; //starting money
	int computerHP = 100;

	int wave = 0;

	TTF_Font* font;
	SDL_Renderer* renderer;
	
	std::vector<MessageBox> messageBoxes;

public:
	game() {};
	game(SDL_Renderer*, TTF_Font*);

	int getMoney() const { return money; };
	void subtractMoney(int);
	void addMoney(int);

	int getHP() const { return computerHP; };
	void giveDamage(int);

	void showTutorial();

	MessageBox getFirstMessageBox() const { return messageBoxes[0]; };
	
	game& game::operator=(const game &rhs) { //Equality overload
		money = rhs.money;
		computerHP = rhs.computerHP;
		wave = rhs.wave;
		font = rhs.font;
		renderer = rhs.renderer;
		return *this;
	}

};
#endif