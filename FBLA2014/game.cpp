#include "game.h"


game::game(SDL_Renderer* SDLrenderer, TTF_Font* TTFfont) {
	renderer = SDLrenderer;
	font = TTFfont;
}
void game::subtractMoney(int cost) {
	money -= cost;
}
void game::addMoney(int cost) {
	money += cost;
}

void game::giveDamage(int damage) {
	computerHP -= damage;
}

void game::showTutorial() {
	std::string firstTextString = "Welcome to Bob's Tower Defense. In this game, you must defend your computer from malicious files attempting to attack" +
		std::string("your computer. Use the mouse to select turrets to place on the map and ") +
		"right click to stop create turret mode. Press escape to exit";
	messageBoxes.push_back(MessageBox(firstTextString.c_str(), renderer, font));

	std::string secondTextString = std::string("There are 3 different turrets in this game, the most important being the scanner, ") +
		"which allows you (and your other turrets) to see whether a file is malicious or not. You must have a scanner scanning a block" +
		"if you want any files within it to be shot at. Use the quarantine turret to temporarily stun an enemy, and finally the delete" +
		"turret to deal damage to an enemy. If the enemy makes it past your defenses, your computer takes damage. Carefully watch your credits!";
	messageBoxes.push_back(MessageBox(secondTextString.c_str(), renderer, font));

	std::string thirdTextString = std::string("The first enemy you'll face is the boot sector virus, an old virus that originated from floppy disks. When someone starts a computer with a ") +
		"floppy disk in it that contains a boot sector virus, the C drive will be infected. Once the floppy is removed, the user may not even realize that their computer has been infected.";
	messageBoxes.push_back(MessageBox(thirdTextString.c_str(), renderer, font));

}

bool game::hasNextBox() {
	bool hasNext = false;
	if (messageBoxes.size() > 1) {
		hasNext = true;
	}
	return hasNext;
}

void game::nextBox() {

	messageBoxes.erase(messageBoxes.begin());
}

void game::waveComplete() {
	++wave;
	
}

File game::getEnemy() {
	return (fileChoices[rand() % fileChoices.size()]);
}