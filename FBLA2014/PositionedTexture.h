#include <SDL.h>

#ifndef POSITIONED_TEXTURE_H
#define POSITIONED_TEXTURE_H

class PositionedTexture { //Holds texture and it's x-y positioning
	SDL_Texture* texture;

	SDL_Rect dstrect;

	int displayLevel;


	public :
		PositionedTexture();
		PositionedTexture(SDL_Texture*, int, int, int, int, int); //Constructor
		PositionedTexture(SDL_Texture*, SDL_Rect, int);//Constructor
		SDL_Texture* getTexture() const { return texture; };
		int getXPos() const{ return dstrect.x; };
		int getYPos() const{ return dstrect.y; };
		const SDL_Rect* getRect() const { return (&dstrect); }; 
		int getLevel() const { return displayLevel; };
		void setRect(int, int, int, int);


		PositionedTexture& PositionedTexture::operator=(const PositionedTexture &rhs) {
			texture = rhs.texture;
			displayLevel = rhs.displayLevel;
			dstrect = rhs.dstrect;
			return *this;
		}



		
};

#endif