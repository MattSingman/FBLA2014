#include "turret.h"

turret::turret(const char* turretType, PositionedTexture turretTexture) {
	type = turretType;
	posTexture = turretTexture;

	if (type == "scanner") { //The cost of one scanner
		cost = 800;
	}
	else if (type == "delete") {
		cost = 200; 
	}
	else {
		//Quar TODO learn to spell that
		cost = 50;
	}
}