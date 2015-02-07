#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "PositionedTexture.h"
#include "Block.h"

#ifndef PATH_BLOCK_H
#define PATH_BLOCK_H

class PathBlock : public Block {
	

	const char* movementDirection;

public:
	PathBlock();
	PathBlock(const char*, const char*, window*, int, int, const char*); //constructor

	const char* const getMovementDirection() { return movementDirection; }; 

	PathBlock& PathBlock::operator=(const PathBlock &rhs) { //Equality overload
		containerWindow = rhs.containerWindow;
		pathScanned = rhs.pathScanned;
		pathUnscanned = rhs.pathUnscanned;
		posTexture = rhs.posTexture;
		scannedTexture = rhs.scannedTexture;
		unScannedTexture = rhs.unScannedTexture;
		gridX = rhs.gridX;
		gridY = rhs.gridY;
		scanned = rhs.scanned;
		movementDirection = rhs.movementDirection;
		return *this;
	}
};

#endif