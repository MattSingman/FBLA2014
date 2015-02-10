#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "PositionedTexture.h"


#ifndef TEXT_TEXTURE_H
#define TEXT_TEXTURE_H
class window;
class TextTexture {
	SDL_Renderer* renderer;

	const char* text;
	SDL_Color color;
	SDL_Texture* texture;
	PositionedTexture posTexture;
	TTF_Font* font;

	int xPos;
	int yPos;

	int width;
	int height;


public:
	TextTexture(const char*, SDL_Color, TTF_Font*, int, int, SDL_Renderer*);
	const char* getText() const { return text; };
	void setText(const char* change) { text = change; };
	int getWidth() const { return width; };
	int getHeight() const { return height; };

	SDL_Color getColor() const { return color; };

	PositionedTexture getPosTexture() const { return posTexture; };
};

#endif