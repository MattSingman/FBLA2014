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
	int computerHP = 100; //Computer health, must stay above 0

	int wave = 0; //What wave the game is on

	TTF_Font* font;
	SDL_Renderer* renderer;
	
	std::vector<MessageBox> messageBoxes; //dialog boxes

	std::vector<File> fileChoices; //Different files that can be placed on the map

	bool alive = true; //Whether computer is still alive

	bool endGame = false; //If game is over (win or lose)

	int enemiesLeft = 0; //Enemies left on given wave

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