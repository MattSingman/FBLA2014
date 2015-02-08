#include "TextTexture.h"

TextTexture::TextTexture(const char* textToDisplay, SDL_Color displayColor, int x, int y, SDL_Renderer* windowRenderer) {
	text = textToDisplay;
	color = displayColor;
	renderer = windowRenderer;

	xPos = x;
	yPos = y;
	TTF_Init();
	font = TTF_OpenFont("../art/Fonts/font.ttf", 25);
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);

	const char* le = TTF_GetError();
	//Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	width = textSurface->w;
	height = textSurface->h;

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	posTexture = PositionedTexture(texture, x, y, width, height, 0);
}
