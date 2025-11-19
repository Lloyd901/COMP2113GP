#include "HangmanGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>
#include <algorithm>

HangmanGame::HangmanGame() : MiniGame("Hangman猜词") {
    hangmanImages = {
        "    /-------\n    |\n    |\n    |\n    |\n    ^^^\n",
        "    /-------]\n    |\n    |\n    |\n    |\n    ^^^\n",
        "    /-------]\n    |       O\n    |\n    |\n    |\n    ^^^\n",
        "    /-------]\n    |       O\n    |       |\n    |       |\n    |\n    ^^^\n",
        "    /-------]\n    |       O\n    |      \\|\n    |       |\n    |\n    ^^^\n",
        "    /------]\n    |      O\n    |     \\|/\n    |      |\n    |\n    ^^^\n",
        "    /-------]\n    |       O\n    |      \\|/\n    |       | \n    |      /\n    ^^^\n",
        "    /-------]\n    |       O\n    |      \\|/\n    |       |\n    |      / \\\n    ^^^\n"
    };
    
    words = {
        "APPLE", "TABLE", "CHAIR", "LIGHT", "HOUSE", "WATER",
        "BREAD", "PLANT", "SMILE", "TRAIN", "MONEY", "PIANO",
        "STONE", "CANDY", "CLOUD", "PEACE", "MOUSE", "GLASS",
        "BEACH", "HEART", "PEACH", "DANCE", "FRUIT", "TIGER"
    };
}

void HangmanGame::play() {
    std::string word = words[Utils::getRandomInt(0, words.size() - 1)];
    std::vector<char> wrongGuesses;
    std::string progress(word.length(), '_');
    int count = 0;
    
    std::cout << ColorCode::RED << "单词：" << progress << ColorCode::RESET << std::endl;
    
    while (wrongGuesses.size() < hangmanImages.size() - 1 && progress != word) {
        std::cout << ColorCode::YELLOW << "请输入你的猜测：" << ColorCode::RESET;
        std::string input;
        std::getline(std::cin, input);
        input = Utils::trim(input);
        
        while (input.length() != 1 || !Utils::isAlpha(input)) {
            std::cout << ColorCode::RED << "无效输入。请再次输入你的猜测：" << ColorCode::RESET;
            std::getline(std::cin, input);
            input = Utils::trim(input);
        }
        
        count++;
        char guess = toupper(input[0]);
        
        bool found = false;
        for (size_t i = 0; i < word.length(); i++) {
            if (word[i] == guess) {
                progress[i] = guess;
                found = true;
            }
        }
        
        if (!found) {
            if (std::find(wrongGuesses.begin(), wrongGuesses.end(), guess) == wrongGuesses.end()) {
                wrongGuesses.push_back(guess);
            }
        }
        
        std::cout << hangmanImages[wrongGuesses.size()] << std::endl;
        std::cout << ColorCode::CYAN << "错误的字母：" << ColorCode::RESET;
        for (char c : wrongGuesses) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
        std::cout << ColorCode::MAGENTA << "尝试次数：" << count << ColorCode::RESET << std::endl;
        std::cout << ColorCode::RED << "单词：" << progress << ColorCode::RESET << std::endl;
    }
    
    if (progress == word) {
        std::cout << ColorCode::BLUE << "恭喜！你赢了 🥳" << ColorCode::RESET << std::endl;
    } else {
        std::cout << ColorCode::RED << "哦不！你输了 🥺\n单词是：" << word << "。再试一次！" << ColorCode::RESET << std::endl;
    }
}
