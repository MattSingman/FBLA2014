#include "WallBlock.h"

WallBlock::WallBlock(const char* unscannedPath, const char* scannedPath, window* parentWindow, int xGrid, int yGrid) {
	pathScanned = scannedPath;
	pathUnscanned = unscannedPath;
	containerWindow = parentWindow;

	gridX = xGrid;
	gridY = yGrid;

	xPos = gridX * 64;
	yPos = gridY * 64;

	
}

void WallBlock::addTurret(const char* turretType, PositionedTexture childTexture) {
	empty = false;

	childTexture.setRect(gridX * getItemWidth(), gridY * getItemHeight(), getItemHeight(), getItemWidth());
	childTurret = turret(turretType, childTexture);
	
}

void WallBlock::removeTurret() {
	empty = true;
	//Effectively ignores turret TODO make it nullable?

}

void WallBlock::checkFireChances(std::vector<PathBlock>* pathBlocks) {
	childTurret.markFrame();
	if (!isEmpty()) {
		if (childTurret.getType() == "quarantine" || childTurret.getType() == "delete") {

			for (auto& pathBlock : *pathBlocks) { //TODO make it pick the target more logically
				if (pathBlock.hasFiles() && pathBlock.getScanned() && childTurret.getFramesUntilNextShot() == 0) {
					if (abs(pathBlock.getGridX() - gridX) <= 2 && abs(pathBlock.getGridY() - gridY) <= 2) {
							std::vector<File>& files = pathBlock.getFiles();
							File& target = files[0];
							if (target.isEnemy()) {
								childTurret.fire(target);
							}
					}
				}
			}
		}
	}
}