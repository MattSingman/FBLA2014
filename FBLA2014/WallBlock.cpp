#include "WallBlock.h"

WallBlock::WallBlock(const char* unscannedPath, const char* scannedPath, window* parentWindow, int xGrid, int yGrid) {
	pathScanned = scannedPath;
	pathUnscanned = unscannedPath;
	containerWindow = parentWindow;

	gridX = xGrid;
	gridY = yGrid;

	xPos = gridX * 64;
	yPos = gridY * 64;

	
}

void WallBlock::addTurret(const char* turretType, PositionedTexture childTexture) {
	empty = false;

	childTexture.setRect(gridX * getItemWidth(), gridY * getItemHeight(), getItemHeight(), getItemWidth());
	childTurret = turret(turretType, childTexture);
	
}