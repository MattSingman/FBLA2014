#include <SDL.h>
#include "PositionedTexture.h"

PositionedTexture::PositionedTexture(SDL_Texture* text, int x, int y, int w, int h) {
	texture = text;
	xPos = x;
	yPos = y;

	dstrect.x = xPos;
	dstrect.y = yPos;
	dstrect.h = h; 
	dstrect.w = w; 



}

PositionedTexture::PositionedTexture(SDL_Texture* text, SDL_Rect posRect) {
	texture = text;
	dstrect = posRect;

	xPos = dstrect.x;
	yPos = dstrect.y;

}
PositionedTexture::PositionedTexture() {};