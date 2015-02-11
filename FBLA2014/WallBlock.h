#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "PositionedTexture.h"
#include "Block.h"
#include "turret.h"
#include "PathBlock.h"
#include "File.h"

#ifndef WALL_BLOCK_H
#define WALL_BLOCK_H

class WallBlock : public Block {
	bool empty = true; //If block has turret on it

	turret childTurret; //Turret on block

public:
	WallBlock();
	WallBlock(const char*, const char*, window*, int, int); //constructor

	bool isEmpty() const { return empty; };
	void setEmpty(bool change) { empty = change; };

	void addTurret(const char*, PositionedTexture); 
	turret getChildTurret() const { return childTurret; };

	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };
	int getXPos() const { return posTexture.getXPos(); };
	int getYPos() const { return posTexture.getYPos(); };

	void removeTurret();

	void checkFireChances(std::vector<PathBlock>*); //will look for chances of turret to fire, if applicable


	WallBlock& WallBlock::operator=(const WallBlock &rhs) { //Equality overload
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
		empty = rhs.empty;
		childTurret = rhs.childTurret;
		return *this;
	}
};

#endif