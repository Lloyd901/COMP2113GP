#include "RockPaperScissorsGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>
#include <vector>

RockPaperScissorsGame::RockPaperScissorsGame() : MiniGame("石头剪刀布") {}

char RockPaperScissorsGame::getComputerChoice() {
    std::vector<char> choices = {'P', 'S', 'R'};
    return choices[Utils::getRandomInt(0, 2)];
}

void RockPaperScissorsGame::play() {
    int playerScore = 0;
    int computerScore = 0;
    int round = 1;
    bool firstRound = true;
    
    while (true) {
        if (firstRound) {
            std::cout << ColorCode::MAGENTA << std::string(100, '-') << ColorCode::RESET << std::endl;
            std::cout << ColorCode::MAGENTA << "欢迎来到石头剪刀布游戏！" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::MAGENTA << "游戏共5轮，五局三胜制。" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::MAGENTA << "\"P\" 代表布, \"S\" 代表剪刀, \"R\" 代表石头。" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::MAGENTA << "如果输了或平局，你将有机会重试，直到击败电脑。" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::MAGENTA << "让我们试着击败电脑吧！" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::MAGENTA << std::string(100, '-') << ColorCode::RESET << std::endl;
            firstRound = false;
        }
        
        if (round > 5) {
            if (playerScore > computerScore) {
                std::cout << ColorCode::CYAN << "太棒了！你赢得了游戏！你击败了电脑！恭喜！" << ColorCode::RESET << std::endl;
                break;
            } else if (computerScore > playerScore) {
                std::cout << ColorCode::RED << "哦不！电脑赢了！再试一次！我相信你这次能赢！" << ColorCode::RESET << std::endl;
                playerScore = 0;
                computerScore = 0;
                round = 1;
            } else {
                std::cout << ColorCode::RED << "啊哈！这次是平局！再试一次！加油！我相信你这次能赢！" << ColorCode::RESET << std::endl;
                playerScore = 0;
                computerScore = 0;
                round = 1;
            }
            continue;
        }
        
        std::cout << "第 " << round << " / 5 轮" << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        std::cout << ColorCode::BLUE << "选择板：" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::BLUE << "布、剪刀还是石头？请输入 \"P\"、\"S\" 或 \"R\" 来表示 \"布\"、\"剪刀\" 或 \"石头\"：" << ColorCode::RESET;
        
        std::string input;
        std::getline(std::cin, input);
        input = Utils::trim(input);
        
        if (input.empty()) continue;
        char choice = tolower(input[0]);
        
        if (choice != 'p' && choice != 's' && choice != 'r') {
            std::cout << ColorCode::RED << "无效输入。请输入 \"P\"、\"S\" 或 \"R\"。" << ColorCode::RESET << std::endl;
            continue;
        }
        
        char computerChoice = getComputerChoice();
        
        if ((choice == 's' && computerChoice == 'P') ||
            (choice == 'p' && computerChoice == 'R') ||
            (choice == 'r' && computerChoice == 'S')) {
            playerScore++;
            std::cout << "电脑的选择：" << computerChoice << std::endl;
            std::cout << ColorCode::CYAN << "啊哈！你赢了这一轮！恭喜！" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "分数板：你 " << playerScore << " : " << computerScore << " 电脑" << ColorCode::RESET << std::endl;
            round++;
        } else if ((choice == 's' && computerChoice == 'S') ||
                   (choice == 'p' && computerChoice == 'P') ||
                   (choice == 'r' && computerChoice == 'R')) {
            playerScore++;
            computerScore++;
            std::cout << "电脑的选择：" << computerChoice << std::endl;
            std::cout << ColorCode::CYAN << "啊哈！平局！继续！" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "分数板：你 " << playerScore << " : " << computerScore << " 电脑" << ColorCode::RESET << std::endl;
            round++;
        } else {
            computerScore++;
            std::cout << "电脑的选择：" << computerChoice << std::endl;
            std::cout << ColorCode::RED << "哦不！电脑赢了！但别担心！我相信你会赢下一轮！" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::RED << "分数板：你 " << playerScore << " : " << computerScore << " 电脑" << ColorCode::RESET << std::endl;
            round++;
        }
    }
}

