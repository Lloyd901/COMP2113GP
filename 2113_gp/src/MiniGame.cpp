#include "MiniGame.h"

MiniGame::MiniGame(const std::string& name) : gameName(name) {}

std::string MiniGame::getGameName() const {
    return gameName;
}

