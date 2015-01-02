#include <SDL.h>

#ifndef POSITIONED_TEXTURE_H
#define POSITIONED_TEXTURE_H

class PositionedTexture { //Holds texture and it's x-y positioning
	SDL_Texture* texture;
	int xPos; 
	int yPos;
	SDL_Rect dstrect;



	public :
		PositionedTexture();
		PositionedTexture(SDL_Texture*, int, int, int, int); //Constructor
		PositionedTexture(SDL_Texture*, SDL_Rect);//Constructor
		SDL_Texture* getTexture() const { return texture; };
		int getXPos() const{ return xPos; };
		int getYPos() const{ return yPos; };
		SDL_Rect* getRect() { return (&dstrect); };


		PositionedTexture& PositionedTexture::operator=(const PositionedTexture &rhs) {
			texture = rhs.texture;
			xPos = rhs.xPos;
			yPos = rhs.yPos;
			dstrect = rhs.dstrect;
			return *this;
		}
};

#endif