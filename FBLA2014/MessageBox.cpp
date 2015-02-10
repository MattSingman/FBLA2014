#include "MessageBox.h"

MessageBox::MessageBox(const char* text, SDL_Renderer* sdlRenderer, TTF_Font* ttfFont) {
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(ttfFont, text, white, 550);

	//Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, textSurface);
	int width = textSurface->w;
	int height = textSurface->h;

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	posTextureText = PositionedTexture(texture, 425, 220, width, height, 0);

	SDL_Surface* textSurfaceEnter = TTF_RenderText_Solid(ttfFont, "Press enter to continue...", white);

	//Create texture from surface pixels
	SDL_Texture* textureEnter = SDL_CreateTextureFromSurface(sdlRenderer, textSurfaceEnter);
	int widthEnter = textSurfaceEnter->w;
	int heightEnter = textSurfaceEnter->h;

	//Get rid of old surface
	SDL_FreeSurface(textSurfaceEnter);

	posTextureOK = PositionedTexture(textureEnter, 540, 520, widthEnter, heightEnter, 0);

}