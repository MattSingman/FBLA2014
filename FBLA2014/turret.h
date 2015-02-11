#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "PositionedTexture.h"
#include "Button.h"
#include "File.h"


#ifndef TURRET_H
#define TURRET_H

class turret : public Button {
	
	const char* type; //Type of turret
	const int WIDTH = 64;
	const int HEIGHT = 64;
	
	int cost; //Cost of turret
	int damage=0;//Damage 
	int stunnedCooldown=0; //Time target would be stunned
	int fireRate; //in frames

	int framesUntilNextShot = 0;
public:
	turret() {};
	turret(const char*, PositionedTexture);

	const char* getType() const { return type; };

	int getCost() const { return cost; };
	int getDamage() const { return damage; };
	int getStunCooldown() const { return stunnedCooldown; };

	void markFrame();
	int getFramesUntilNextShot() const { return framesUntilNextShot; };
	void setFramesUntilNextShot(int change) { framesUntilNextShot = change; };

	int getFireRate() const { return fireRate; };

	void fire(File&);

	turret& turret::operator=(const turret &rhs) {
		posTexture = rhs.posTexture;
		type = rhs.type;
		cost = rhs.cost;
		damage = rhs.damage;
		stunnedCooldown = rhs.stunnedCooldown;
		framesUntilNextShot = rhs.framesUntilNextShot;
		fireRate = rhs.fireRate;
		return *this;
	}
	

};

#endif