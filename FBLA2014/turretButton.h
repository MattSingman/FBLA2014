#include "Button.h"
#include "PositionedTexture.h"
#include <SDL.h>


#ifndef TURRET_BUTTON_H
#define TURRET_BUTTON_H

class turretButton : public Button {
	const int WIDTH = 350; //Width of turret button
	const int HEIGHT = 128; //Height of turret button

	const int TURRET_WIDTH = 100;
	const int TURRET_HEIGHT = 100;


	const char* childPath;
	PositionedTexture childPosTexture;

	bool selected = false;

public:
	turretButton();
	turretButton(const char*, const char*, window*); //constructor 

	bool getSelected() { return selected; };
	void setSelected(bool);

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