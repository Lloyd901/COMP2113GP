#include "GameController.h"
#include "MenuSystem.h"
#include "MiniGameManager.h"
#include "ColorCode.h"
#include "Utils.h"
#include <iostream>
#include <exception>

int main() {
    try {
        std::cout << ColorCode::CYAN << "正在启动迷宫游戏（完整版 - 7个小游戏）..." << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "包含：井字棋、猜数字、石头剪刀布、Hangman、推箱子、贪吃蛇、文字冒险" << ColorCode::RESET << std::endl;
        Utils::sleep(2);
        
        MenuSystem menu;
        MiniGameManager gameManager;
        
        bool running = true;
        while (running) {
            MenuSystem::MenuChoice choice = menu.showMainMenu();
            
            switch (choice) {
                case MenuSystem::MenuChoice::MAZE_GAME: {
                    GameController game;
                    game.run();
                    break;
                }
                case MenuSystem::MenuChoice::MINI_GAME: {
                    bool inMiniGameMenu = true;
                    while (inMiniGameMenu) {
                        int gameIndex = menu.showMiniGameMenu();
                        if (gameIndex == -1) {
                            inMiniGameMenu = false;
                        } else {
                            gameManager.playGameByIndex(gameIndex);
                        }
                    }
                    break;
                }
                case MenuSystem::MenuChoice::EXIT: {
                    running = false;
                    break;
                }
            }
        }
        
        std::cout << ColorCode::MAGENTA << "\n感谢游玩！再见！" << ColorCode::RESET << std::endl;
    } catch (const std::exception& e) {
        std::cerr << ColorCode::RED << "错误：" << e.what() << ColorCode::RESET << std::endl;
        return 1;
    }
    
    return 0;
}
