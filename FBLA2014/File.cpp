#include "File.h"

File::File(const char* enemyArt, const char* friendlyArt, bool isEnemy, double speed, int health, int attack, SDL_Renderer* renderer) {
	enemyArtPath = enemyArt;
	friendlyArtPath = friendlyArt;
	enemy = isEnemy;
	movementSpeed = speed;
	hp = health;
	attackDamage = attack;

	preciseXPos = 0.0; xPos = (int)preciseXPos;
	preciseYPos = 704.0; yPos = (int)preciseYPos;

	SDL_Rect dstrect;//SDL_Rect telling location to place, x and y correspond to coords to place surface, from top left
	dstrect.h = HEIGHT; dstrect.w = WIDTH; //Height and width are the same for each item
	dstrect.x = xPos;
	dstrect.y = yPos;


	SDL_Surface* surfaceFriend = IMG_Load(friendlyArtPath);  //Load unscanned texture
	SDL_Texture* textureFriend = SDL_CreateTextureFromSurface(renderer, surfaceFriend); //Create texture
	SDL_FreeSurface(surfaceFriend);
	friendTexture = PositionedTexture(textureFriend, dstrect, 1);

	if (enemy){
		SDL_Surface* surfaceEnemy = IMG_Load(enemyArtPath);  //Load scanned texture
		SDL_Texture* textureEnemy = SDL_CreateTextureFromSurface(renderer, surfaceEnemy); //Create texture
		SDL_FreeSurface(surfaceEnemy);
		enemyTexture = PositionedTexture(textureEnemy, dstrect, 1);
	}
	else { //If not enemy, enemy and friend texture are the same
		enemyTexture = friendTexture;
	}
	if (scanned) {
		posTexture = enemyTexture;
	}
	else {
		posTexture = friendTexture;
	}
}

void File::giveDamage(int damage) {
	hp -= damage;
}

bool File::isAlive() {
	if (hp > 0) {
		return true;
	}
	else {
		return false;
	}
}

void File::setStunned(bool change, int stunnedFrames) {
	stunned = change;
	if (stunned) {
		stunnedFramesLeft = stunnedFrames;
	}
}

void File::move() {

	if (stunnedFramesLeft > 0) {
		--stunnedFramesLeft;
	}
	if (stunnedFramesLeft == 0) {
		stunned = false;
	}

	if (!stunned) {
		if (std::string(movementDirection) == "U") {
			preciseYPos -= movementSpeed;
			yPos = (int)preciseYPos;
		}
		else if (std::string(movementDirection) == "D"){
			preciseYPos += movementSpeed;
			yPos = (int)preciseYPos;
		}
		else if (std::string(movementDirection) == "L"){
			preciseXPos -= movementSpeed;
			xPos = (int)preciseXPos;
		}
		else if (std::string(movementDirection) == "R") {
			preciseXPos += movementSpeed;
			xPos = (int)preciseXPos;
		}
	}

	if (scanned) {
		enemyTexture.setRect(xPos, yPos, HEIGHT, WIDTH);
		posTexture = enemyTexture;
	}
	else {
		friendTexture.setRect(xPos, yPos, HEIGHT, WIDTH);
		posTexture = friendTexture;

	}
}

void File::setScanned(bool change) {
	scanned = change;
	if (scanned) {
		posTexture = enemyTexture;
	}
	else {
		posTexture = friendTexture;
	}
}

PositionedTexture File::getPosTexture() {
	if (scanned) {
		posTexture = enemyTexture;
	}
	else {
		posTexture = friendTexture;
	}
	return posTexture;
}

