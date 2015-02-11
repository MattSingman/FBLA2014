#include "WallBlock.h"

WallBlock::WallBlock(const char* unscannedPath, const char* scannedPath, window* parentWindow, int xGrid, int yGrid) {
	pathScanned = scannedPath; //Path to scanned texture
	pathUnscanned = unscannedPath; //Path to unscanned texture
	containerWindow = parentWindow;

	gridX = xGrid; //Grid position compared to other blocks
	gridY = yGrid;

	xPos = gridX * 64; //actual screen position
	yPos = gridY * 64;

	
}

void WallBlock::addTurret(const char* turretType, PositionedTexture childTexture) {
	empty = false;

	childTexture.setRect(gridX * getItemWidth(), gridY * getItemHeight(), getItemHeight(), getItemWidth()); //Set turret position
	childTurret = turret(turretType, childTexture);
	
}

void WallBlock::removeTurret() {
	empty = true;
	//Effectively ignores turret 

}

void WallBlock::checkFireChances(std::vector<PathBlock>* pathBlocks) { //See if turret can fire on any enemies
	childTurret.markFrame(); 
	if (!isEmpty()) { //If there is a turret
		if (childTurret.getType() == "quarantine" || childTurret.getType() == "delete") { //If turret can fire

			for (auto& pathBlock : *pathBlocks) {  //Look at all the path blocks
				if (pathBlock.hasFiles() && pathBlock.getScanned() && childTurret.getFramesUntilNextShot() == 0) { //If path block has files, is scanned, and turret can fire
					if (abs(pathBlock.getGridX() - gridX) <= 2 && abs(pathBlock.getGridY() - gridY) <= 2) { //If within range of 2
							std::vector<File>& files = pathBlock.getFiles();
							File& target = files[0]; 
							if (target.isEnemy()) {
								childTurret.fire(target);//Fire upon first file if enemy
							}
					}
				}
			}
		}
	}
}