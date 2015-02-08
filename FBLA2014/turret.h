#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "PositionedTexture.h"
#include "Button.h"


#ifndef TURRET_H
#define TURRET_H

class turret : public Button {
	
	const char* type; 
	const int WIDTH = 64;
	const int HEIGHT = 64;
	
	int cost;
public:
	turret() {};
	turret(const char*, PositionedTexture);

	int getCost() const { return cost; };

	turret& turret::operator=(const turret &rhs) {
		posTexture = rhs.posTexture;
		type = rhs.type;
		cost = rhs.cost;
		return *this;
	}
	

};

#endif