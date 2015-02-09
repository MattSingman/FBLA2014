#include <SDL.h>
#include<SDL_image.h>
#include <string>
#include "PositionedTexture.h"

#ifndef FILE_H
#define FILE_H

class File {

	const int WIDTH = 32;
	const int HEIGHT = 32;

	const char* enemyArtPath; //Art to be displayed if enemy and under scanner
	const char* friendlyArtPath; //Art to be displayed if not under scanner

	bool enemy;  //Whether the file is a virus or not when put under the scanner
	bool scanned = false; //Whether file is being scanned

	bool stunned = false;
	int stunnedFramesLeft;

	const char* movementDirection;

	double movementSpeed; //in pixels/frame

	int hp;

	int attackDamage; //How much damage is dealt when it gets to the end of the map

	PositionedTexture posTexture;
	PositionedTexture enemyTexture;
	PositionedTexture friendTexture;

	int xPos;
	int yPos;

	double preciseXPos;
	double preciseYPos;

public:
	File() {};
	File(const char*, const char*, bool, double, int,int, SDL_Renderer*);

	const int getWidth() const { return WIDTH; };
	const int getHeight() const { return HEIGHT; };
	int getXPos() const { return xPos; };
	int getYPos() const { return yPos; };

	bool isEnemy() const { return enemy; };

	bool isScanned() const { return scanned; };
	void setScanned(bool);

	bool getStunned() const { return stunned; };
	void setStunned(bool);

	const char* getMovementDirection() const { return movementDirection; };
	void setMovementDirection(const char* newDirection) { movementDirection = newDirection; };


	double getMovementSpeed() const { return movementSpeed; };

	int getHP() const { return hp; };
	void giveDamage(int);
	bool isAlive();

	int getAttackDamage() const { return attackDamage; };

	void move();

	PositionedTexture getPosTexture();

	File& File::operator=(const File &rhs) { //Equality overload
		enemy = rhs.enemy;
		scanned = rhs.scanned;
		enemyArtPath = rhs.enemyArtPath;
		friendlyArtPath = rhs.friendlyArtPath;
		movementDirection = rhs.movementDirection;
		movementSpeed = rhs.movementSpeed;
		posTexture = rhs.posTexture;
		enemyTexture = rhs.enemyTexture;
		friendTexture = rhs.friendTexture;
		xPos = rhs.xPos;
		yPos = rhs.yPos; 
		preciseXPos = rhs.preciseXPos;
		preciseYPos = rhs.preciseYPos;
		hp = rhs.hp;
		attackDamage = rhs.attackDamage;
		return *this;
	}
	File& File::operator=(const int &rhs) { //Equality overload
		if (rhs == NULL) {
			enemy = NULL;
			scanned = NULL;
			enemyArtPath = NULL;
			friendlyArtPath = NULL;
			movementDirection = NULL;
			movementSpeed = NULL;
			xPos = NULL;
			yPos = NULL;
			preciseXPos = NULL;
			preciseYPos = NULL;
			hp = NULL;
			attackDamage = NULL;
		}
		return *this;
	}
	
	bool File::operator==(const File &rhs) {
		return (isEnemy() == rhs.isEnemy() && getXPos() == rhs.getXPos() &&
			getYPos() == rhs.getYPos());
	}
};



#endif