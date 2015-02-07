#include "Block.h"

#include "window.h"

//Constructor
Block::Block(const char* unscannedPath, const char* scannedPath, window* parentWindow, int xGrid, int yGrid) {
	pathScanned = scannedPath;
	pathUnscanned = unscannedPath;
	containerWindow = parentWindow;

	gridX = xGrid;
	gridY = yGrid;

}
Block::Block() {} //Default constructor

PositionedTexture Block::placeOnScreen(int x, int y) {
	SDL_Rect dstrect;//SDL_Rect telling location to place button, x and y correspond to coords to place surface, from top left
	dstrect.h = HEIGHT; dstrect.w = WIDTH; //Height and width are the same for each item
	dstrect.x = x;
	dstrect.y = y;

	SDL_Surface* surfaceScan = IMG_Load(pathScanned);  //Load scanned texture
	SDL_Texture* textureScan = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surfaceScan); //Create texture
	//SDL_FreeSurface(surfaceScan);
	scannedTexture = PositionedTexture(textureScan, dstrect, 0);

	SDL_Surface* surfaceUnScan = IMG_Load(pathUnscanned);  //Load unscanned texture
	SDL_Texture* textureUnScan = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surfaceUnScan); //Create texture
	//SDL_FreeSurface(surfaceUnScan);
	unScannedTexture = PositionedTexture(textureUnScan, dstrect, 0);

	if (scanned) {
		posTexture = scannedTexture;
	}
	else {
		posTexture = unScannedTexture;
	}
	return posTexture;

}


void Block::setScanned(bool change) {
	scanned = change;
	if (scanned) {
		posTexture = scannedTexture;
	}
	else {
		posTexture = unScannedTexture;
	}
}

