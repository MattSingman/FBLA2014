#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "PositionedTexture.h"

#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

class MessageBox {

	PositionedTexture posTextureText;
	PositionedTexture posTextureOK;

public:
	MessageBox(const char*,SDL_Renderer*, TTF_Font*);

	PositionedTexture getPosTextureText() const { return posTextureText; };
	PositionedTexture getPosTextureOK() const { return posTextureOK; };
};

#endif