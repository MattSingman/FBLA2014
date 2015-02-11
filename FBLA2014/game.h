#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <algorithm>
#include "MessageBox.h"
#include "File.h"

#ifndef GAME_H
#define GAME_H

class game {

	int money = 1000; //starting money
	int computerHP = 100;

	int wave = 0;

	TTF_Font* font;
	SDL_Renderer* renderer;
	
	std::vector<MessageBox> messageBoxes;

	std::vector<File> fileChoices;

	bool alive = true;

	bool endGame = false;

	int enemiesLeft = 0;

public:
	game() {};
	game(SDL_Renderer*, TTF_Font*);

	int getMoney() const { return money; };
	void subtractMoney(int);
	void addMoney(int);

	int getHP() const { return computerHP; };
	void giveDamage(int);

	int getEnemiesLeft() const { return enemiesLeft; };

	void showTutorial();
	bool hasNextBox();
	
	void nextBox();

	bool isAlive() const { return alive; };

	bool getEndGame() const { return endGame; };

	void waveComplete();

	File getEnemy();

	MessageBox getFirstMessageBox() const { return messageBoxes[0]; };
	
	game& game::operator=(const game &rhs) { //Equality overload
		money = rhs.money;
		computerHP = rhs.computerHP;
		wave = rhs.wave;
		font = rhs.font;
		renderer = rhs.renderer;
		messageBoxes = rhs.messageBoxes;
		fileChoices = rhs.fileChoices;
		enemiesLeft = rhs.enemiesLeft;
		alive = rhs.alive;
		return *this;
	}

};
#endif