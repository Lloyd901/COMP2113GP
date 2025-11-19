#include "GuessNumberGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>

GuessNumberGame::GuessNumberGame() : MiniGame("猜数字游戏") {}

void GuessNumberGame::play() {
    int target = Utils::getRandomInt(1, 100);
    std::cout << ColorCode::MAGENTA << "欢迎来到猜数字游戏！" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "请猜一个1到100之间的整数。" << ColorCode::RESET << std::endl;
    
    bool correct = false;
    while (!correct) {
        std::cout << ColorCode::MAGENTA << "请输入你的猜测（1-100之间的整数）：" << ColorCode::RESET;
        std::string input;
        std::getline(std::cin, input);
        input = Utils::trim(input);
        
        if (!Utils::isDigit(input)) {
            std::cout << ColorCode::RED << "无效输入。请输入1到100之间的整数。" << ColorCode::RESET << std::endl;
            continue;
        }
        
        int guess = std::stoi(input);
        if (guess < 1 || guess > 100) {
            std::cout << ColorCode::RED << "无效输入。请输入1到100之间的整数。" << ColorCode::RESET << std::endl;
            continue;
        }
        
        int diff = guess - target;
        if (diff == 0) {
            std::cout << ColorCode::CYAN << "答对了！恭喜你！" << ColorCode::RESET << std::endl;
            correct = true;
        } else if (diff < 0) {
            int absDiff = -diff;
            if (absDiff >= 90) {
                std::cout << ColorCode::YELLOW << "太小了！比正确值小90以上。" << ColorCode::RESET << std::endl;
            } else if (absDiff >= 10) {
                std::cout << ColorCode::YELLOW << "太小了！比正确值小" << (absDiff/10)*10 << "以上。" << ColorCode::RESET << std::endl;
            } else {
                std::cout << ColorCode::YELLOW << "非常接近了！比正确值小不到10！" << ColorCode::RESET << std::endl;
            }
        } else {
            if (diff >= 90) {
                std::cout << ColorCode::YELLOW << "太大了！比正确值大90以上。" << ColorCode::RESET << std::endl;
            } else if (diff >= 10) {
                std::cout << ColorCode::YELLOW << "太大了！比正确值大" << (diff/10)*10 << "以上。" << ColorCode::RESET << std::endl;
            } else {
                std::cout << ColorCode::YELLOW << "非常接近了！比正确值大不到10！" << ColorCode::RESET << std::endl;
            }
        }
    }
}

