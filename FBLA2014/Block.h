#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "PositionedTexture.h"
#include "Button.h"

#ifndef BLOCK_H
#define BLOCK_H
class window;


class Block {
protected:
	window* containerWindow; //Window button is located in

	SDL_Texture* texture;
	PositionedTexture posTexture; //Texture of block


	const char* pathScanned; //Path to item's art
	const char* pathUnscanned;
	const int WIDTH = 64; //Width of item
	const int HEIGHT = 64; //Height of item
	PositionedTexture scannedTexture; //Texture to be displayed when under influence of scanner
	PositionedTexture unScannedTexture; 

	int gridX; //Grid positioning compared to other blocks
	int gridY;

	int xPos;
	int yPos;

	bool scanned = false;

	

public:
	Block();
	Block(const char*, const char*, window*, int, int); //constructor 
	PositionedTexture placeOnScreen(int x, int y); //Places item on screen at given location 

	int getGridX() const { return gridX; };
	int getGridY() const { return gridY; };
	int getXPos() const { return posTexture.getXPos(); };
	int getYPos() const { return posTexture.getYPos(); };
	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };




	bool getScanned() const { return scanned; };
	void setScanned(bool);

	window* getContainerWindow() const { return containerWindow; };
	SDL_Texture* getSDLTexture() const { return texture; };
	PositionedTexture getTexture() const { return posTexture; };

	bool insidePos(int, int); //Checks whether given position is inside block


	Block& Block::operator=(const Block &rhs) { //Equality overload
		containerWindow = rhs.containerWindow;
		pathScanned = rhs.pathScanned;
		pathUnscanned = rhs.pathUnscanned;
		posTexture = rhs.posTexture;
		scannedTexture = rhs.scannedTexture;
		unScannedTexture = rhs.unScannedTexture;
		gridX = rhs.gridX;
		gridY = rhs.gridY;
		xPos = rhs.xPos;
		yPos = rhs.yPos;
		scanned = rhs.scanned;
		return *this;
	}
};

#endif