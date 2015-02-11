#include "Button.h"
#include "PositionedTexture.h"
#include <SDL.h>


#ifndef TURRET_BUTTON_H
#define TURRET_BUTTON_H

class turretButton : public Button {


	const int TURRET_WIDTH = 64;
	const int TURRET_HEIGHT = 64;


	const char* childPath;
	PositionedTexture childPosTexture;

	const char* turretType; //Scanner etc

	bool selected = false;

public:
	turretButton();
	turretButton(const char*, const char*, window*, const char*); //constructor 

	bool getSelected() { return selected; };
	void setSelected(bool);

	const char* getTurretType() const { return turretType; };

	void setChildPosition(int, int);

	PositionedTexture getChildPosTexture() const { return childPosTexture; };

	PositionedTexture placeOnScreen(int, int);

	turretButton& turretButton::operator=(const turretButton &rhs) { //Equality overload
		containerWindow = rhs.containerWindow;
		path = rhs.path;
		texture = rhs.texture;
		posTexture = rhs.posTexture;
		childPath = rhs.childPath;
		childPosTexture = rhs.childPosTexture;
		selected = rhs.selected;
		return *this;
	}
};

#endif