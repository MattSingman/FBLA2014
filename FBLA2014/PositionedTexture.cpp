#include <SDL.h>
#include "PositionedTexture.h"

PositionedTexture::PositionedTexture(SDL_Texture* text, int x, int y, int w, int h, int level) {
	texture = text;


	dstrect.x = x;
	dstrect.y = y;
	dstrect.h = h; 
	dstrect.w = w; 

	displayLevel = level;

}

PositionedTexture::PositionedTexture(SDL_Texture* text, SDL_Rect posRect, int level) {
	texture = text;
	dstrect = posRect;

	displayLevel = level;

}
void PositionedTexture::setRect(int x, int y, int h, int w) {
	dstrect.x = x;
	dstrect.y = y;
	dstrect.h = h;
	dstrect.w = w;
	

}
PositionedTexture::PositionedTexture() {};