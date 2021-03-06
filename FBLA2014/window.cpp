#include "window.h"

window::window() { //TODO: 

	SDL_Init(SDL_INIT_EVERYTHING);//initialize SDL
	mainWindow = SDL_CreateWindow("Bob's Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 32); //create Window 

	SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN); 
	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED); //Create renderer
	screen = SDL_GetWindowSurface(mainWindow); //screen is on window
	createMenu();
	srand(time(NULL)); //Random number seed

	//Start FPS counter
	fpsTimer.start(); 

	TTF_Init(); //Start the font creator
	textFont = TTF_OpenFont("../art/Fonts/font.ttf", 25);

	while (!quit) { //main loop 
		//Start fps cap timer
		capTimer.start();

		while (SDL_PollEvent(&e) != 0) {
			if (!inGame) { //If in menu
				//If user quits
				if (e.type == SDL_QUIT) {
					quit = true;
				} 
				else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) { //If user clicks with left mouse button
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					MenuItem selected;
					for (auto& menuItem : menuItems) { //Check to see if any menu items were target of click
						if (menuItem.insidePos(mouseX, mouseY)) {
							selected = menuItem;
							break;
						}
					}
					if (selected.getFunction() != NULL) { //Make sure object exists
						(selected.getFunction())(); //Execute function of that menu button
					}
				}
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) { //Escape closes the game
					quit = true;
				}
				else if (e.type = SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN && dialogBox && frameUntilNextKeyPressRegistered == 0) { //If game is over, quit once user passes end screen
					frameUntilNextKeyPressRegistered = 10;
					if (currentGame.getEndGame()) {
						quit = true;
					}


				}
			}
			else { //If playing
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && dialogBox == false) { //If left mouse click
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					for (auto& turretButton : turretButtons) { //See if click was on turret button
						if (turretButton.insidePos(mouseX, mouseY)) {
							turretButton.setSelected(true);
							int xMouse, yMouse;
							SDL_GetMouseState(&xMouse, &yMouse); 
							turretButton.setChildPosition(xMouse, yMouse); //turret icon will follow mouse
							textures.push_back(turretButton.getChildPosTexture());
							for (auto& turretButtonCheck : turretButtons) {
								if (&turretButtonCheck != &turretButton) {
									turretButtonCheck.setSelected(false); //Selecting one deselects others
								}
							}
							break;
						}
					}
					for (auto& wallBlock : wallBlocks) { 
						if (wallBlock.insidePos(mouseX, mouseY) && wallBlock.isEmpty()) { //If click was in one of the wall blocks
							const char* turretType = "";
							PositionedTexture turretTexture;
							for (auto& turretButton : turretButtons) {
								if (turretButton.getSelected()) { //If clicked on wall block while turret button was selected
									turretType = turretButton.getTurretType(); 
									turretTexture = turretButton.getChildPosTexture();
									break;
								}
							}
							if (turretType != "") {
								wallBlock.addTurret(turretType, turretTexture); //Add turret to the block
								currentGame.subtractMoney(wallBlock.getChildTurret().getCost());
								if (currentGame.getMoney() < 0) { //If player cannot pay for the turret
									currentGame.addMoney(wallBlock.getChildTurret().getCost());
									wallBlock.removeTurret(); //remove
									
								}
								else { //if the purchase was valid
									if (turretType == "scanner") { //If user purchased scanner
										int blockX = wallBlock.getGridX();
										int blockY = wallBlock.getGridY();

										for (auto& wallBlockScan : wallBlocks) { //Set wallBlocks as scanned if they are within 2 blocks
											int checkBlockX = wallBlockScan.getGridX();
											int checkBlockY = wallBlockScan.getGridY();
											if (abs(blockX - checkBlockX) <= 2 && abs(blockY - checkBlockY) <= 2) {
												wallBlockScan.setScanned(true);
											}
										}
										for (auto& pathBlockScan : pathBlocks) { //pathBlocks are scanned if within 2 blocks
											int checkBlockX = pathBlockScan.getGridX();
											int checkBlockY = pathBlockScan.getGridY();
											if (abs(blockX - checkBlockX) <=2 && abs(blockY - checkBlockY) <= 2) {
												pathBlockScan.setScanned(true);
											}
										}
									}
								}
							}
							break;
						}
					}
				}
				else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT && dialogBox == false) { //If right click
					for (auto& turretButton : turretButtons) { 
						if (turretButton.getSelected()) {
							turretButton.setSelected(false); //Deselect any selected turret buttons
						}
					}
				}
				else if (e.type == SDL_MOUSEMOTION && dialogBox == false) { //Turret button icon follows mouse
					for (auto& turretButton : turretButtons) {
						if (turretButton.getSelected()) {
							int mouseX, mouseY;
							SDL_GetMouseState(&mouseX, &mouseY);
							turretButton.setChildPosition(mouseX, mouseY);
						}
					}
				}
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) { //Quit on escape
					quit = true;
				}
				else if (e.type = SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN && dialogBox && frameUntilNextKeyPressRegistered == 0) {
					frameUntilNextKeyPressRegistered = 10;
					if (!currentGame.hasNextBox()) { //Advance dialog boxes on enter
						dialogBox = false;
					}
					currentGame.nextBox();


				}


			}
			
		}
		if (inGame) { //Screen must be updated if in game
			if (!(currentGame.isAlive())) {
				dialogBox = true;
				inGame = false;
			}
			if (addFileCooldown > 0) { //Cooldown for adding files, decremented every screen
				--addFileCooldown;
			}
			
			textures.clear();
			
			for (auto& wallBlock : wallBlocks) { 
				textures.push_back(wallBlock.getTexture()); //Add wallBlock textures
				if (!(wallBlock.isEmpty())) {
					wallBlock.checkFireChances(&pathBlocks); //Try to fire if possible
					textures.push_back(wallBlock.getChildTurret().getTexture()); //Add any child turret textures
				}
			}
			for (auto& pathBlock : pathBlocks) {
				if (addFileCooldown == 0 && currentGame.getEnemiesLeft() > 0 && !dialogBox) { //If need to add enemies, add enemy on first block
					if (pathBlock.getGridX() == 0 && pathBlock.getGridY() == 11 ) {
						pathBlock.addFile(currentGame.getEnemy()); 
						addFileCooldown = 120;
					}
				}
				textures.push_back(pathBlock.getTexture()); //Add path block
				pathBlock.checkFiles(&pathBlocks, &currentGame);  //Remove from pathBlock if file left
				std::vector<File>& pathBlockFiles = (pathBlock.getFiles());
				if (pathBlockFiles.size()) {
					for (auto& file : pathBlockFiles) {
						file.move(); //Move file
						textures.push_back(file.getPosTexture());
					}
				}
			}
			for (auto& turretButton : turretButtons) { //Add turret buttons
				textures.push_back(turretButton.getTexture());
				if (turretButton.getSelected()) {
					textures.push_back(turretButton.getChildPosTexture());
				}
			}
			SDL_Color white = { 255, 255, 255 }; //The color white, for coloring the font
			//Create text box for money count
			int moneyCount = currentGame.getMoney();
			std::string moneyCountString = "Money:" + std::to_string(moneyCount) + " Credits"; //Convert int to string for display
			const char* moneyCountCString = moneyCountString.c_str();
			TextTexture money = TextTexture(moneyCountCString, white, textFont, 1066, 500, renderer);
			textures.push_back(money.getPosTexture());

			//Create text box for HP
			int hpCount = currentGame.getHP();
			std::string hpString = "HP:" + std::to_string(hpCount) + "%"; //Convert int to string for display
			const char* hpCString = hpString.c_str();
			TextTexture hp = TextTexture(hpCString, white, textFont, 1066, 550, renderer);
			textures.push_back(hp.getPosTexture());


			if (!dialogBox) {

				bool enemiesOnScreen = false; //Check if enemies on screen
				for (auto& pathBlock : pathBlocks) {
					
					if (pathBlock.hasFiles()) {
						for (auto& file : pathBlock.getFiles()) {
							if (file.isEnemy()) {
								enemiesOnScreen = true;
								break;
							}
						}
					}
				}
				if (!enemiesOnScreen && currentGame.getEnemiesLeft() == 0) { //If enemies all gone and no more will be added, end of wave
					currentGame.waveComplete();
					dialogBox = true;
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


		for (int i = 0; i <= MAX_LEVEL; ++i) {
			for (auto texture : textures) {
				if (texture.getLevel() == i) {
					SDL_RenderCopy(renderer, texture.getTexture(), NULL, texture.getRect());
				}
				
			}

		}
		if (dialogBox) { //Draw dialog box if needed
			SDL_Rect dialogBoxRect = { 400, 200, 600, 350 };
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &dialogBoxRect);

			MessageBox boxToDisplay = currentGame.getFirstMessageBox();
			SDL_RenderCopy(renderer, boxToDisplay.getPosTextureText().getTexture(), NULL, boxToDisplay.getPosTextureText().getRect());
			SDL_RenderCopy(renderer, boxToDisplay.getPosTextureOK().getTexture(), NULL, boxToDisplay.getPosTextureOK().getRect());

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
		if (frameUntilNextKeyPressRegistered > 0) {
			--frameUntilNextKeyPressRegistered; //One key press would register twice without cooldown
		}
	}
	close(); //If quit, close window 
}
//Loads surface and places it on the screen
void window::loadBackgroundSurface(std::string path){ 
	SDL_Surface* artSurface = IMG_Load(path.c_str()); //Load background

	background = NULL;
	background = SDL_CreateTextureFromSurface(getRenderer(), artSurface); //Create texture
	SDL_FreeSurface(artSurface);
} 

void window::close() {
	//Destroy window
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	//Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	textFont = NULL; //Destroy font
	TTF_CloseFont(textFont);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();	
	TTF_Quit();
}
//start a new game
void window::newGame() {
	inGame = true;
	loadBackgroundSurface("../art/gameBackground.bmp"); //load game background
	textures.clear();

	turretButton deleteButton = turretButton("../art/deleteButton.bmp", "../art/delete.bmp",this, "delete"); //Button to select different turrets
	turretButtons.push_back(deleteButton);

	turretButton quarantineButton = turretButton("../art/quarantineButton.bmp", "../art/quarantine.bmp",  this, "quarantine");
	turretButtons.push_back(quarantineButton);

	turretButton scannerButton = turretButton("../art/scannerButton.bmp", "../art/scanner.bmp", this, "scanner");
	turretButtons.push_back(scannerButton);

	int xPosition = SCREEN_WIDTH;
	for (int i = 0; i < turretButtons.size(); ++i) { //Add buttons to select turret
		PositionedTexture positionTexture = turretButtons[i].placeOnScreen(xPosition, (128 * i) + 128);
		textures.push_back(positionTexture);
	}

	gamePath = { //Array holds path that enemies will go down. N means not walkable block; U, D, L, R correspond to direction enemy will go. 
		//(Up, down, left or right)
		{ "" }, //Computer tower
		{ "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "U", "N" },
		{ "N", "N", "N", "N", "N", "N", "N", "N", "N", "R", "R", "R", "D", "N", "U", "N" },
		{ "N", "N", "N", "N", "N", "N", "N", "N", "N", "U", "N", "N", "D", "N", "U", "N" },
		{ "N", "N", "N", "N", "N", "N", "N", "N", "N", "U", "N", "N", "D", "N", "U", "N" },
		{ "N", "N", "N", "N", "N", "N", "N", "N", "N", "U", "N", "N", "D", "N", "U", "N" },
		{ "R", "R", "R", "R", "R", "R", "D", "N", "N", "U", "N", "N", "D", "N", "U", "N" },
		{ "U", "N", "N", "N", "N", "N", "D", "N", "N", "U", "N", "D", "L", "N", "U", "N" },
		{ "U", "L", "L", "L", "N", "N", "D", "N", "N", "U", "N", "D", "N", "N", "U", "N" },
		{ "N", "N", "N", "U", "N", "N", "D", "N", "N", "U", "N", "R", "R", "R", "U", "N" },
		{ "N", "N", "N", "U", "N", "N", "D", "N", "N", "U", "N", "N", "N", "N", "N", "N" },
		{ "R", "R", "R", "U", "N", "N", "R", "R", "R", "U", "N", "N", "N", "N", "N", "N" }
	};
	//Add Blocks TODO make it more dynamic to screen res
	for (int i = 1; i < 12; ++i) {//Loop through each height, leaving one slot at the top
		for (int j = 0; j < 16; ++j) {//Loop through each width
			if (gamePath[i][j] == "N") {
				WallBlock newBlock = WallBlock("../art/block.bmp", "../art/blockScanned.bmp", this, j, i);
				newBlock.placeOnScreen(j * 64, i * 64);
				textures.push_back(newBlock.getTexture());
				wallBlocks.push_back(newBlock);
			}
			else {
				PathBlock newPathBlock = PathBlock("../art/path.bmp", "../art/pathScanned.bmp", j, i, gamePath[i][j].c_str(), this);
				newPathBlock.placeOnScreen(j * 64, i * 64);
				textures.push_back(newPathBlock.getTexture());
				pathBlocks.push_back(newPathBlock);
			}
			
		}
	}

	currentGame = game(renderer, textFont);
	currentGame.showTutorial();
	dialogBox = true;
	



}


//Quits program
void window::quitWindow() {
	quit = true;
}
//Creates menu with options
void window::createMenu() {
	loadBackgroundSurface("../art/menu.bmp");//Load the startup menu

	std::function<void()> newGameFunction = std::bind(&window::newGame,this);
	MenuItem newGameOption = MenuItem("../art/newGame.bmp", newGameFunction, this);  //New game option
	menuItems.push_back(newGameOption); //Adds to array of MenuItems

	std::function<void()> quitWindowFunction = std::bind(&window::quitWindow,this);
	MenuItem quitOption = MenuItem("../art/quit.bmp", quitWindowFunction, this); //Quit
	menuItems.push_back(quitOption);

	int distanceAllotted = (getScreenHeight() - (2 * getMenuItemY())) / menuItems.size(); //distance for each item is the space allowed to the items divided by the number of items
	//TODO distance allotted
	for (size_t i = 0; i < menuItems.size(); ++i) {
		PositionedTexture j = menuItems[i].placeOnScreen(getMenuItemX(), (getMenuItemY()+ (i* distanceAllotted)));//Place each MenuItem on screen TODO Y POS
		textures.push_back(j);
	}


}
