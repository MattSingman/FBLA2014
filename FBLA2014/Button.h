#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <functional>
#include "PositionedTexture.h"

#ifndef BUTTON_H
#define BUTTON_H

class window;

class Button {
protected:
	window* containerWindow; //Window button is located in
	const char* path; //Path to item's art
	const int WIDTH = 300; //Width of item
	const int HEIGHT = 100; //Height of item
	SDL_Texture* texture;
	PositionedTexture posTexture;


public:
	Button();
	Button(const char*, window*); //constructor TODO: Param for animation? 
	window* getContainerWindow() const { return containerWindow; };
	SDL_Texture* getSDLTexture() const { return texture; };
	PositionedTexture getTexture() const { return posTexture; };
	PositionedTexture placeOnScreen(int x, int y); //Places item on screen at given location (IMPORTANT: X location is at CENTER)

	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };
	int getXPos() const { return posTexture.getXPos(); };
	int getYPos() const { return posTexture.getYPos(); };


	bool insidePos(int, int);

	Button& Button::operator=(const Button &rhs) { //Equality overload
		containerWindow = rhs.containerWindow;
		path = rhs.path;
		texture = rhs.texture;
		posTexture = rhs.posTexture;
		return *this;
	}

};

#endif