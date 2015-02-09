#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <algorithm> 
#include "PositionedTexture.h"
#include "Block.h"
#include "File.h"
#include "game.h"

#ifndef PATH_BLOCK_H
#define PATH_BLOCK_H

class PathBlock : public Block {
	
	std::vector<File> files;

	const char* movementDirection;



public:
	PathBlock();
	PathBlock(const char*, const char*, int, int, const char*, window*); //constructor

	const char* const getMovementDirection() { return movementDirection; }; 

	void addFile(File);

	std::vector<File>& getFiles() { return files; };
	bool hasFiles();

	void checkFiles(std::vector<PathBlock>*, game*);
	bool isInsideBlock(File);

	void giveTurret(File, std::vector<PathBlock>*, game*);

	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };
	int getXPos() const { return posTexture.getXPos(); };
	int getYPos() const { return posTexture.getYPos(); };

	void setScanned(bool);


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