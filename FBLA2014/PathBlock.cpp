#include "PathBlock.h"

PathBlock::PathBlock(const char* unscannedPath, const char* scannedPath, window* parentWindow, int xGrid, int yGrid, const char* direction) {
	pathScanned = scannedPath;
	pathUnscanned = unscannedPath;
	containerWindow = parentWindow;

	gridX = xGrid;
	gridY = yGrid;

	movementDirection = direction; //Direction enemies will move while inside this block
}