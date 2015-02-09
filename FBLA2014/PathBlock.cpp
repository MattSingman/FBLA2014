#include "PathBlock.h"

PathBlock::PathBlock(const char* unscannedPath, const char* scannedPath, int xGrid, int yGrid, const char* direction, window* parentWindow) {
	pathScanned = scannedPath;
	pathUnscanned = unscannedPath;
	containerWindow = parentWindow;

	gridX = xGrid;
	gridY = yGrid;

	movementDirection = direction; //Direction enemies will move while inside this block
}

void PathBlock::addFile(File toAdd) {
	toAdd.setMovementDirection(getMovementDirection());
	toAdd.setScanned(getScanned());
	files.push_back(toAdd);
}

bool PathBlock::isInsideBlock(File fileToCheck) {
	bool inside = true;

	int fileWidth = fileToCheck.getWidth(); int fileHeight = fileToCheck.getHeight();
	int fileX = fileToCheck.getXPos(); int fileY = fileToCheck.getYPos();


	if (insidePos(fileX, fileY) || //Check to see if box has any part inside of Block
		insidePos(fileX + fileWidth, (fileY)) || 
		insidePos(fileX, fileY + fileHeight) ||
		insidePos((fileX - fileWidth), (fileY - fileHeight)));
		//remains inside

	else {
		inside = false; //Otherwise all 4 corners are outside of box
	}

	return inside;
}

void PathBlock::checkFiles(std::vector<PathBlock>* pathBlocks, game* currentGame) {
	std::vector<int> indexesToRemove;
	for (int i = 0; i < files.size(); ++i) {
		if (!(isInsideBlock(files[i]))) { //If outside block
			giveTurret(files[i], pathBlocks, currentGame);
			files.resize(std::remove(files.begin(), files.end(), files[i]) - files.begin());
		}
	}
}

void PathBlock::giveTurret(File fileToGive, std::vector<PathBlock>* pathBlocks, game* currentGame) {
	int nextGridX = gridX;
	int nextGridY = gridY;
	//Get next path block
	if (std::string(movementDirection) == "U") {
		nextGridY -= 1;
	}
	else if (std::string(movementDirection) == "D") {
		nextGridY += 1;
	}
	else if (std::string(movementDirection) == "L") {
		nextGridX -= 1;
	}
	else if (std::string(movementDirection) == "R"){
		nextGridX += 1;
	}

	bool gaveFile = false;
	for (auto& pathBlock : *pathBlocks) {
		int i = pathBlock.getGridX(); int y = pathBlock.getGridY();
		if (pathBlock.getGridX() == nextGridX && pathBlock.getGridY() == nextGridY) {
			pathBlock.addFile(fileToGive);
			gaveFile = true;
			break;
		}

	}
	if (!gaveFile) { //If no other path found, it hit the end and will hurt the computer HP
		currentGame->giveDamage(fileToGive.getAttackDamage());
	}
}

void PathBlock::setScanned(bool change) {
	scanned = change;
	if (scanned) {
		posTexture = scannedTexture;
	}
	else {
		posTexture = unScannedTexture;
	}
	if (files.size() > 0) {
		for (auto& file : files) {
			file.setScanned(scanned);
		}
	}
}