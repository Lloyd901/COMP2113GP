#include "MenuSystem.h"
#include "Utils.h"
#include "ColorCode.h"
#include "MiniGameManager.h"
#include <iostream>

MenuSystem::MenuSystem() {
    avatars = {
        {1, "😋"}, {2, "🤓"}, {3, "😎"}, {4, "🤩"}, {5, "😊"}
    };
}

std::string MenuSystem::selectAvatar() {
    while (true) {
        std::cout << ColorCode::MAGENTA << "按指定的数字选择你的头像：" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::MAGENTA << "        1-->😋" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::MAGENTA << "        2-->🤓" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::MAGENTA << "        3-->😎" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::MAGENTA << "        4-->🤩" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::MAGENTA << "        5-->😊" << ColorCode::RESET << std::endl;
        
        std::string input;
        std::getline(std::cin, input);
        input = Utils::trim(input);
        
        if (Utils::isDigit(input)) {
            int choice = std::stoi(input);
            if (avatars.find(choice) != avatars.end()) {
                return avatars[choice];
            }
        }
        std::cout << ColorCode::RED << "无效输入。请按1-5之间的数字。" << ColorCode::RESET << std::endl;
    }
}

MenuSystem::MenuChoice MenuSystem::showMainMenu() {
    while (true) {
        Utils::clearScreen();
        std::cout << ColorCode::MAGENTA << R"(
[]           []     [][][] []    [] [][][] [] []     [] [][][][][] []    []
[]          [][]    []  []  []  []  []  [] [] [][]   []     []     []    []
[]         []  []   [][]      []    [][]   [] [] []  []     []     [][][][]
[]        [][][][]  []  []    []    [] []  [] []  [] []     []     []    []
[][][][] []      [] [][][]    []    []  [] [] []   [][]     []     []    []
)" << ColorCode::RESET << std::endl;
        
        std::cout << ColorCode::YELLOW << "欢迎来到迷宫游戏 - 完整版（包含全部7个小游戏）" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "请选择你想玩的模式：" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "        1 --> 迷宫游戏（带小游戏）" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "        2 --> 单独玩小游戏" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "        3 --> 退出游戏" << ColorCode::RESET << std::endl;
        std::cout << "==> ";
        
        std::string choice;
        std::getline(std::cin, choice);
        choice = Utils::trim(choice);
        
        if (choice == "1") {
            return MenuChoice::MAZE_GAME;
        } else if (choice == "2") {
            return MenuChoice::MINI_GAME;
        } else if (choice == "3") {
            return MenuChoice::EXIT;
        } else {
            std::cout << ColorCode::RED << "无效输入。请输入 '1', '2' 或 '3'" << ColorCode::RESET << std::endl;
            Utils::sleep(1);
        }
    }
}

MenuSystem::GameSettings MenuSystem::showMazeGameMenu() {
    GameSettings settings;
    
    while (true) {
        Utils::clearScreen();
        std::cout << ColorCode::YELLOW << "迷宫游戏设置" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "请选择游戏模式：" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "        1-->快速游戏" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "        2-->自定义游戏" << ColorCode::RESET << std::endl;
        std::cout << "==> ";
        
        std::string choice;
        std::getline(std::cin, choice);
        choice = Utils::trim(choice);
        
        while (choice != "1" && choice != "2") {
            std::cout << ColorCode::RED << "无效输入。请输入 '1' 或 '2'" << ColorCode::RESET << std::endl;
            std::cout << "==> ";
            std::getline(std::cin, choice);
            choice = Utils::trim(choice);
        }
        
        settings.playerAvatar = selectAvatar();
        std::cout << ColorCode::CYAN << "你选择了：" << settings.playerAvatar << ColorCode::RESET << std::endl;
        
        if (choice == "2") {
            std::cout << ColorCode::CYAN << "选择迷宫大小：" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    1-->等级 1(23x23)" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    2-->等级 2(25x25)" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    3-->等级 3(27x27)" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    4-->等级 4(29x29)" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    5-->等级 5(31x31)" << ColorCode::RESET << std::endl;
            std::cout << "=> ";
            
            std::string sizeInput;
            std::getline(std::cin, sizeInput);
            sizeInput = Utils::trim(sizeInput);
            
            while (sizeInput < "1" || sizeInput > "5") {
                std::cout << ColorCode::RED << "无效输入。请输入1到5之间的数字" << ColorCode::RESET << std::endl;
                std::cout << "=> ";
                std::getline(std::cin, sizeInput);
                sizeInput = Utils::trim(sizeInput);
            }
            settings.mazeSize = std::stoi(sizeInput) + 10;
            
            std::cout << ColorCode::CYAN << "选择小游戏密度：" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    1-->等级 1" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    2-->等级 2" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "                    3-->等级 3" << ColorCode::RESET << std::endl;
            std::cout << "=> ";
            
            std::string densityInput;
            std::getline(std::cin, densityInput);
            densityInput = Utils::trim(densityInput);
            
            while (densityInput < "1" || densityInput > "3") {
                std::cout << ColorCode::RED << "无效输入。请输入1到3之间的数字" << ColorCode::RESET << std::endl;
                std::cout << "=> ";
                std::getline(std::cin, densityInput);
                densityInput = Utils::trim(densityInput);
            }
            settings.minigameDensity = std::stoi(densityInput) * 2;
        } else {
            settings.mazeSize = Utils::getRandomInt(11, 15);
            settings.minigameDensity = 2;
        }
        
        std::cout << ColorCode::CYAN << "准备好开始了吗？" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::CYAN << "            1-->开始  2-->返回菜单" << ColorCode::RESET << std::endl;
        std::cout << "=> ";
        
        std::string confirm;
        std::getline(std::cin, confirm);
        confirm = Utils::trim(confirm);
        
        if (confirm == "1") {
            return settings;
        }
    }
}

int MenuSystem::showMiniGameMenu() {
    MiniGameManager tempManager;
    
    while (true) {
        Utils::clearScreen();
        std::cout << ColorCode::CYAN << "========== 小游戏选择 ==========" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::YELLOW << "请选择你想玩的小游戏：" << ColorCode::RESET << std::endl;
        
        for (int i = 0; i < tempManager.getGameCount(); i++) {
            std::cout << ColorCode::YELLOW << "        " << (i + 1) << " --> " 
                      << tempManager.getGameName(i) << ColorCode::RESET << std::endl;
        }
        std::cout << ColorCode::YELLOW << "        0 --> 返回主菜单" << ColorCode::RESET << std::endl;
        std::cout << "==> ";
        
        std::string choice;
        std::getline(std::cin, choice);
        choice = Utils::trim(choice);
        
        if (Utils::isDigit(choice)) {
            int index = std::stoi(choice);
            if (index == 0) {
                return -1;
            } else if (index >= 1 && index <= tempManager.getGameCount()) {
                return index - 1;
            }
        }
        
        std::cout << ColorCode::RED << "无效输入。请输入0到" << tempManager.getGameCount() 
                  << "之间的数字" << ColorCode::RESET << std::endl;
        Utils::sleep(1);
    }
}
