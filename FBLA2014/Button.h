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
	
	SDL_Texture* texture;
	PositionedTexture posTexture; //Texture for button

	const int WIDTH = 300;
	const int HEIGHT = 100;
	


public:
	Button();
	Button(const char*, window*); //constructor 
	window* getContainerWindow() const { return containerWindow; };
	SDL_Texture* getSDLTexture() const { return texture; };
	PositionedTexture getTexture() const { return posTexture; };
	PositionedTexture placeOnScreen(int x, int y); 


	int getXPos() const { return posTexture.getXPos(); };
	int getYPos() const { return posTexture.getYPos(); };

	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };


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