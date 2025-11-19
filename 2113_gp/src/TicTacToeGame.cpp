#include "TicTacToeGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>

TicTacToeGame::TicTacToeGame() : MiniGame("井字棋") {}

void TicTacToeGame::initBoard() {
    board = {
        {"1", "2", "3"},
        {"4", "5", "6"},
        {"7", "8", "9"}
    };
}

void TicTacToeGame::printBoard() {
    std::cout << ColorCode::YELLOW << std::string(90, '-') << ColorCode::RESET << std::endl;
    std::cout << ColorCode::YELLOW << "加油！我们一定能击败电脑！" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::YELLOW << std::string(90, '-') << ColorCode::RESET << std::endl;
    for (const auto& row : board) {
        for (size_t i = 0; i < row.size(); i++) {
            std::cout << "| " << row[i] << " |";
        }
        std::cout << std::endl;
    }
}

bool TicTacToeGame::isPositionTaken(int pos) {
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    return board[row][col] == "😊" || board[row][col] == "🐱";
}

void TicTacToeGame::playerMove() {
    while (true) {
        std::cout << "😊: ";
        std::string input;
        std::getline(std::cin, input);
        input = Utils::trim(input);
        
        if (!Utils::isDigit(input)) {
            std::cout << ColorCode::RED << "错误：无效输入。请输入1到9之间的整数。" << ColorCode::RESET << std::endl;
            printBoard();
            continue;
        }
        
        int pos = std::stoi(input);
        if (pos < 1 || pos > 9) {
            std::cout << ColorCode::RED << "错误：无效输入。请输入1到9之间的整数。" << ColorCode::RESET << std::endl;
            printBoard();
            continue;
        }
        
        if (isPositionTaken(pos)) {
            std::cout << ColorCode::RED << "错误：该位置已被选择。请选择另一个位置。" << ColorCode::RESET << std::endl;
            printBoard();
            continue;
        }
        
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        board[row][col] = "😊";
        break;
    }
}

void TicTacToeGame::computerMove() {
    int pos;
    do {
        pos = Utils::getRandomInt(1, 9);
    } while (isPositionTaken(pos));
    
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    board[row][col] = "🐱";
}

bool TicTacToeGame::checkWin(const std::string& symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;
    
    return false;
}

bool TicTacToeGame::isBoardFull() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell != "😊" && cell != "🐱")
                return false;
        }
    }
    return true;
}

void TicTacToeGame::play() {
    initBoard();
    
    std::cout << ColorCode::MAGENTA << std::string(90, '-') << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "欢迎来到井字棋游戏！" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << std::string(90, '-') << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "在这个游戏中，你将是笑脸😊，电脑将是猫🐱。" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "你将先走棋，电脑将在你走后移动。" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "你的任务是击败电脑。" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << std::string(90, '-') << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "你可以通过输入1到9之间的整数来选择和占据一个位置，" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "未选择的剩余位置的序列号显示在下面的棋盘中。" << ColorCode::RESET << std::endl;
    
    printBoard();
    
    bool firstRound = true;
    while (true) {
        if (!firstRound) {
            printBoard();
        }
        firstRound = false;
        
        playerMove();
        if (checkWin("😊")) {
            printBoard();
            std::cout << ColorCode::CYAN << "恭喜！你赢了！" << ColorCode::RESET << std::endl;
            break;
        }
        
        if (isBoardFull()) {
            printBoard();
            std::cout << ColorCode::RED << "没有人赢！再试一次！我相信你这次会赢！" << ColorCode::RESET << std::endl;
            initBoard();
            continue;
        }
        
        computerMove();
        if (checkWin("🐱")) {
            printBoard();
            std::cout << ColorCode::RED << "哦不！你输了！加油！再试一次！！你这次一定会赢！" << ColorCode::RESET << std::endl;
            initBoard();
            continue;
        }
        
        if (isBoardFull()) {
            printBoard();
            std::cout << ColorCode::RED << "没有人赢！再试一次！我相信你这次会赢！" << ColorCode::RESET << std::endl;
            initBoard();
            continue;
        }
    }
}

