#include "GameController.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>

void GameController::run() {
    auto settings = menu.showMazeGameMenu();
    
    player = std::make_unique<Player>(settings.playerAvatar);
    
    maze = std::make_unique<Maze>(settings.mazeSize, settings.mazeSize, 
                              settings.playerAvatar, settings.minigameDensity);
    
    Utils::clearScreen();
    maze->print();
    
    bool gameOver = false;
    auto [startY, startX] = maze->getStartPosition();
    int playerY = startY, playerX = startX;
    
    while (!gameOver) {
        std::cout << "请输入移动方向 (wasd)：";
        std::string input;
        std::getline(std::cin, input);
        input = Utils::trim(input);
        
        if (input.empty()) continue;
        
        bool validInput = true;
        for (char c : input) {
            if (c != 'w' && c != 'a' && c != 's' && c != 'd') {
                std::cout << ColorCode::RED << "输入无效。请输入移动方向 (wasd)：" << ColorCode::RESET << std::endl;
                validInput = false;
                break;
            }
        }
        
        if (!validInput) continue;
        
        for (char direction : input) {
            bool reachedEnd = maze->move(playerY, playerX, direction, gameManager);
            Utils::clearScreen();
            maze->print();
            
            if (reachedEnd) {
                std::cout << ColorCode::RED << "游戏结束！" << ColorCode::RESET << std::endl;
                std::cout << ColorCode::CYAN << "恭喜你！你成功走出了迷宫！" << ColorCode::RESET << std::endl;
                std::cout << ColorCode::MAGENTA << "\n感谢您的游玩！" << ColorCode::RESET << std::endl;
                Utils::sleep(2);
                gameOver = true;
                break;
            }
        }
    }
}
