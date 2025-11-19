#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "MenuSystem.h"
#include "Maze.h"
#include "Player.h"
#include "MiniGameManager.h"
#include <memory>

class GameController {
private:
    MenuSystem menu;
    std::unique_ptr<Maze> maze;
    std::unique_ptr<Player> player;
    MiniGameManager gameManager;
    
public:
    void run();
};

#endif // GAMECONTROLLER_H

