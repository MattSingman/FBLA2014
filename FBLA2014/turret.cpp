#include "turret.h"

turret::turret(const char* turretType, PositionedTexture turretTexture) {
	type = turretType;
	posTexture = turretTexture;

	if (type == "scanner") { //The cost of one scanner
		cost = 800;
	}
	else if (type == "delete") {
		cost = 200; 
		damage = 1;
		fireRate = 120;
	}
	else {
		//Quar TODO learn to spell that
		cost = 50;
		stunnedCooldown = 30; //frames
		fireRate = 180;
	}
}

void turret::markFrame() {
	if (framesUntilNextShot != 0) {
		--framesUntilNextShot;
	}
}

void turret::fire(File& target) {
	if (type == "delete") {
		target.giveDamage(damage);
	}
	else if (type == "quarantine") {
		target.setStunned(true, stunnedCooldown);
	}

	framesUntilNextShot += fireRate;
}

