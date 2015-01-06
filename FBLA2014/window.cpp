#include <functional>
#include "window.h"

window::window() { //TODO: Music
	SDL_Init(SDL_INIT_EVERYTHING);//initialize SDL
	mainWindow = SDL_CreateWindow("GAMENAMEHERE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 32); //create Window TODO: Change window name

	//SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN); TODO Final game full screen
	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED); //Create renderer
	screen = SDL_GetWindowSurface(mainWindow); //screen is on window
	loadBackgroundSurface("../art/menu.bmp");//Load the startup menu
	createMenu();
	
	//Start FPS counter
	fpsTimer.start();


	while (!quit) { //main menu loop TODO: seperate function when running game?
		//Start fps cap timer
		capTimer.start();

		while (SDL_PollEvent(&e) != 0) {
			if (!inGame) { //If in menu
				//If user quits
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				else if (e.type == SDL_MOUSEBUTTONUP) {
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					MenuItem selected;
					for (auto& menuItem : menuItems) {
						if (menuItem.insidePos(mouseX, mouseY)) {
							selected = menuItem;
							break;
						}
					}
					if (selected.getSDLTexture() != NULL) { //Make sure object exists
						(selected.getFunction())();
					}
				}
			}
			else { //If playing
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
		}
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}
		//Clear screen
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background, NULL, NULL); //Render background

		for (auto texture : textures) {
			if (texture.getXPos() && texture.getYPos()) { //Position, if applicable
				SDL_RenderCopy(renderer, texture.getTexture(), NULL, texture.getRect());
			}
			else {
				SDL_RenderCopy(renderer, texture.getTexture(), NULL, NULL);
			}
		}

		//Update screen
		SDL_RenderPresent(renderer);
		++countedFrames;
		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME) {
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
	close(); //If quit, close window TODO
}
//Loads surface and places it on the screen
void window::loadBackgroundSurface(std::string path){ //TODO Will I be able to chnage the background?
	SDL_Surface* artSurface = IMG_Load(path.c_str()); //Load background

	background = NULL;
	background = SDL_CreateTextureFromSurface(getRenderer(), artSurface); //Create texture
	SDL_FreeSurface(artSurface);
} 

void window::close() { //TODO MenuItems close themselves
	//Destroy window
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
//start a new game
void window::newGame() {
	inGame = true;
	loadBackgroundSurface("../art/gameBackground.bmp"); //load game background

}
//show options
void window::showOptions() {

}
//Shows instructions on how to play
void window::showHelp() {

}
//Quits program
void window::quitWindow() {
	quit = true;
}
//Creates menu with options
void window::createMenu() {

	std::function<void()> newGameFunction = std::bind(&window::newGame,this);
	MenuItem newGameOption = MenuItem("../art/newGame.bmp", newGameFunction, this);  //New game option
	menuItems.push_back(newGameOption); //Adds to array of MenuItems

	std::function<void()> showOptionsFunction = std::bind(&window::showOptions,this);
	MenuItem optionsOption = MenuItem("../art/options.bmp", showOptionsFunction, this);  //Show options menu
	menuItems.push_back(optionsOption);

	std::function<void()> showHelpFunction = std::bind(&window::showHelp,this);
	MenuItem helpOption = MenuItem("../art/help.bmp", showHelpFunction, this); //Show help 
	menuItems.push_back(helpOption);

	std::function<void()> quitWindowFunction = std::bind(&window::quitWindow,this);
	MenuItem quitOption = MenuItem("../art/quit.bmp", quitWindowFunction, this); //Quit
	menuItems.push_back(quitOption);

	int distanceAllotted = (getScreenHeight() - (2 * getMenuItemY())) / menuItems.size(); //distance for each item is the space allowed to the items divided by the number of items
	//TODO distance allotted
	for (size_t i = 0; i < menuItems.size(); ++i) {
		PositionedTexture j = menuItems[i].placeOnScreen(getMenuItemX(), getMenuItemY(), i, distanceAllotted);//Place each MenuItem on screen
		textures.push_back(j);
	}


}
