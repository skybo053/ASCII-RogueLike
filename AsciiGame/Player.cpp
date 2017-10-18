#include "Player.h"



Player::Player(): key(0) {}

void Player::setKey(int num) { key += num; }
int Player::getKey() const { return key; }

bool Player::hasInventory() {
	if (key > 0) {
		return true;
	}
	else
		return false;
}

Player::~Player()
{
}
