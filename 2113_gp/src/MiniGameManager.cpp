#include "MiniGameManager.h"
#include "TicTacToeGame.h"
#include "GuessNumberGame.h"
#include "RockPaperScissorsGame.h"
#include "HangmanGame.h"
#include "SokobanGame.h"
#include "SnakeGame.h"
#include "TextAdventureGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>

MiniGameManager::MiniGameManager() {
    games.push_back(std::make_unique<TicTacToeGame>());
    games.push_back(std::make_unique<GuessNumberGame>());
    games.push_back(std::make_unique<RockPaperScissorsGame>());
    games.push_back(std::make_unique<HangmanGame>());
    games.push_back(std::make_unique<SokobanGame>());
    games.push_back(std::make_unique<SnakeGame>());
    games.push_back(std::make_unique<TextAdventureGame>());
}

void MiniGameManager::playRandomGame() {
    int index = Utils::getRandomInt(0, games.size() - 1);
    std::cout << ColorCode::CYAN << "\n========== 小游戏时间！==========" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::CYAN << "游戏：" << games[index]->getGameName() 
              << " (第" << (index + 1) << "个，共" << games.size() << "个)" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::YELLOW << "提示：所有游戏都有相等的出现几率（各1/" << games.size() << "）" << ColorCode::RESET << std::endl;
    Utils::sleep(1);
    games[index]->play();
    std::cout << ColorCode::CYAN << "========== 小游戏结束 ==========" << ColorCode::RESET << std::endl;
    Utils::sleep(1);
}

void MiniGameManager::playGameByIndex(int index) {
    if (index >= 0 && index < static_cast<int>(games.size())) {
        std::cout << ColorCode::CYAN << "\n========== 小游戏时间！==========" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::CYAN << "游戏：" << games[index]->getGameName() << ColorCode::RESET << std::endl;
        games[index]->play();
        std::cout << ColorCode::CYAN << "========== 小游戏结束 ==========" << ColorCode::RESET << std::endl;
        Utils::sleep(1);
    }
}

int MiniGameManager::getGameCount() const {
    return games.size();
}

std::string MiniGameManager::getGameName(int index) const {
    if (index >= 0 && index < static_cast<int>(games.size())) {
        return games[index]->getGameName();
    }
    return "";
}
