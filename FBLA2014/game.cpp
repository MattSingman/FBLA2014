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
	std::string firstTextString = "Welcome to Bob's Tower Defense. In this game, you must defend your computer from malicious files attempting to attack " +
		std::string("your computer. Use the mouse to select turrets to place on the map and ") +
		"right click to stop create turret mode. Press escape to exit";
	messageBoxes.push_back(MessageBox(firstTextString.c_str(), renderer, font));

	std::string secondTextString = std::string("There are 3 different turrets in this game, the most important being the scanner, ") +
		"which allows you (and your other turrets) to see whether a file is malicious or not. You must have a scanner scanning a block " +
		"if you want any files within it to be shot at. Use the quarantine turret to temporarily stun an enemy, and finally the delete " +
		"turret to deal damage to an enemy. If the enemy makes it past your defenses, your computer takes damage. Carefully watch your credits!";
	messageBoxes.push_back(MessageBox(secondTextString.c_str(), renderer, font));

	std::string thirdTextString = std::string("When a file is under the gaze of the scanner, if the file is malicious, you'll see the file turn red, and turrets can and will shoot it.");
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
	if (wave == 1) {
		enemiesLeft = 10;

		std::string textString = std::string("The first enemy you'll face is the boot sector virus, an old virus that originated from floppy disks. When someone starts a computer with a ") +
			"floppy disk in it that contains a boot sector virus, the C drive will be infected. Once the floppy is removed, the user may not even realize that their computer has been infected.";
		messageBoxes.push_back(MessageBox(textString.c_str(), renderer, font));

		File newEnemy1 = File("../art/floppyDiskEnemy.bmp", "../art/floppyDiskFriend.bmp", true,
			.5, 2, 2, renderer);
		File newEnemy2 = File("../art/floppyDiskEnemy.bmp", "../art/floppyDiskFriend.bmp", false,
			.5, 2, 2, renderer);
		fileChoices.push_back(newEnemy1);
		fileChoices.push_back(newEnemy2);
	}
	else if (wave == 2) {
		enemiesLeft = 10;
		std::string textString = std::string("You downloaded some Word documents! Be careful, Word documents can include macros, which can, if malicious, replace benign macros on your computer and execute unwanted actions");
		messageBoxes.push_back(MessageBox(textString.c_str(), renderer, font));

		File newEnemy1 = File("../art/wordDocumentEnemy.bmp", "../art/wordDocumentFriend.bmp", true,
			1, 5, 5, renderer);
		File newEnemy2 = File("../art/wordDocumentEnemy.bmp", "../art/wordDocumentFriend.bmp", false,
			1, 5, 5, renderer);
		for (int i = 0; i < wave; ++i) {
			fileChoices.push_back(newEnemy1);
			fileChoices.push_back(newEnemy2);
		}
		
		
	}
	else if (wave == 3) {
		enemiesLeft = 10;
		std::string textString = std::string("The next enemy attacking your computer is a browser hijacker, which is attempting to take control of your browser and redirect your web queries!");
		messageBoxes.push_back(MessageBox(textString.c_str(), renderer, font));

		File newEnemy1 = File("../art/browserEnemy.bmp", "../art/browserFriend.bmp", true,
			1.5, 7, 7, renderer);
		File newEnemy2 = File("../art/browserEnemy.bmp", "../art/browserFriend.bmp", false,
			1.5, 7, 7, renderer);
		for (int i = 0; i < wave; ++i) {
			fileChoices.push_back(newEnemy1);
			fileChoices.push_back(newEnemy2);
		}

	}
	else if (wave == 4) {
		enemiesLeft = 10;
		std::string textString = std::string("It looks like you downloaded an executable file. Be wary, some executables may be direct action viruses, or malware that executes upon execution.");
		
		File newEnemy1 = File("../art/directActionEnemy.bmp", "../art/directActionFriend.bmp", true,
			1, 5, 5, renderer);
		File newEnemy2 = File("../art/directActionEnemy.bmp", "../art/directActionFriend.bmp", false,
			1, 5, 5, renderer);
		for (int i = 0; i < wave; ++i) {
			fileChoices.push_back(newEnemy1);
			fileChoices.push_back(newEnemy2);
		}

	}
	else if (wave == 5) {

	}
	else if (wave == 6) {

	}
	else if (wave == 7) {

	}
	else if (wave == 8) {

	}
	else if (wave == 9) {

	} 
	else if (wave == 10) {

	}
	else if (wave == 11) {
		std::string textString = std::string("You WON!!!!");
		messageBoxes.push_back(MessageBox(textString.c_str(), renderer, font));
	}

}

File game::getEnemy() {
	enemiesLeft--;
	return (fileChoices[rand() % fileChoices.size()]);
}