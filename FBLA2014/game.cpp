#include "game.h"

void game::subtractMoney(int cost) {
	money -= cost;
}
void game::addMoney(int cost) {
	money += cost;
}

void game::giveDamage(int damage) {
	computerHP -= damage;
}