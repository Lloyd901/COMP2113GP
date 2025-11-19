#include "Player.h"

Player::Player(const std::string& av) : avatar(av), posY(1), posX(1) {}

std::string Player::getAvatar() const { return avatar; }
int Player::getY() const { return posY; }
int Player::getX() const { return posX; }
void Player::setPosition(int y, int x) { posY = y; posX = x; }
