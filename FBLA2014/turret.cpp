#include "turret.h"

turret::turret(const char* turretType, PositionedTexture turretTexture) {
	type = turretType;
	posTexture = turretTexture;

	if (type == "scanner") { //The cost of one scanner
		cost = 800;
	}
	else if (type == "delete") { //Cost of delete. Delete does damage 
		cost = 200; 
		damage = 1;
		fireRate = 120;
	}
	else { //Quar stuns
		cost = 50;
		stunnedCooldown = 30; //frames
		fireRate = 180;
	}
}

void turret::markFrame() { //Count down cool down for shooting
	if (framesUntilNextShot != 0) {
		--framesUntilNextShot;
	}
}

void turret::fire(File& target) {
	if (type == "delete") {
		target.giveDamage(damage); //Give damage to target
	}
	else if (type == "quarantine") {
		target.setStunned(true, stunnedCooldown); //Stun target
	}

	framesUntilNextShot += fireRate;
}

