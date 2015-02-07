#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "PositionedTexture.h"
#include "Button.h"

#ifndef BLOCK_H
#define BLOCK_H
class window;


class Block : public Button {
protected:
	const char* pathScanned; //Path to item's art
	const char* pathUnscanned;
	const int WIDTH = 64; //Width of item
	const int HEIGHT = 64; //Height of item
	PositionedTexture scannedTexture;
	PositionedTexture unScannedTexture;

	int gridX;
	int gridY;

	bool scanned = false;

	

public:
	Block();
	Block(const char*, const char*, window*, int, int); //constructor TODO: Param for animation? 
	PositionedTexture placeOnScreen(int x, int y); //Places item on screen at given location (IMPORTANT: X location is at CENTER)

	int getGridX() const { return gridX; };
	int getGridY() const { return gridY; };

	bool getScanned() const { return scanned; };
	void setScanned(bool);


	Block& Block::operator=(const Block &rhs) { //Equality overload
		containerWindow = rhs.containerWindow;
		pathScanned = rhs.pathScanned;
		pathUnscanned = rhs.pathUnscanned;
		posTexture = rhs.posTexture;
		scannedTexture = rhs.scannedTexture;
		unScannedTexture = rhs.unScannedTexture;
		gridX = rhs.gridX;
		gridY = rhs.gridY;
		scanned = rhs.scanned;
		return *this;
	}
};

#endif