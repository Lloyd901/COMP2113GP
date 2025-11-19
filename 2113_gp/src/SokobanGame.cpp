#include "SokobanGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>

bool SokobanGame::Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

bool SokobanGame::Position::operator<(const Position& other) const {
    return (x < other.x) || (x == other.x && y < other.y);
}

SokobanGame::SokobanGame() : MiniGame("推箱子") {}

void SokobanGame::parseLevel() {
    boxes.clear();
    targets.clear();
    walls.clear();
    moves = 0;
    
    for (int y = 0; y < (int)level.size(); y++) {
        for (int x = 0; x < (int)level[y].size(); x++) {
            char c = level[y][x];
            Position pos = {x, y};
            
            if (c == 'P') {
                playerPos = pos;
            } else if (c == 'B') {
                boxes.insert(pos);
            } else if (c == '$') {
                targets.insert(pos);
            } else if (c == '#') {
                walls.insert(pos);
            }
        }
    }
}

void SokobanGame::generateLevel() {
    level = {
        "#########",
        "#       #",
        "# $   $ #",
        "#   P   #",
        "# B   B #",
        "#       #",
        "#########"
    };
}

void SokobanGame::drawGame() {
    Utils::clearScreen();
    std::cout << ColorCode::MAGENTA << "\n=== 推箱子游戏 ===" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "移动: (w)上 (s)下 (a)左 (d)右" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "移动次数: " << moves << "\n" << ColorCode::RESET << std::endl;
    
    for (int y = 0; y < (int)level.size(); y++) {
        std::string row = "";
        for (int x = 0; x < (int)level[y].size(); x++) {
            Position pos = {x, y};
            
            if (pos == playerPos) {
                if (targets.find(pos) != targets.end()) {
                    row += "P* ";
                } else {
                    row += "P  ";
                }
            } else if (boxes.find(pos) != boxes.end() && targets.find(pos) != targets.end()) {
                row += "*  ";
            } else if (boxes.find(pos) != boxes.end()) {
                row += "B  ";
            } else if (targets.find(pos) != targets.end()) {
                row += "$  ";
            } else if (walls.find(pos) != walls.end()) {
                row += "#  ";
            } else {
                row += ".  ";
            }
        }
        std::cout << row << std::endl;
    }
}

bool SokobanGame::movePlayer(int dx, int dy) {
    Position newPos = {playerPos.x + dx, playerPos.y + dy};
    
    if (walls.find(newPos) != walls.end()) {
        return false;
    }
    
    if (boxes.find(newPos) != boxes.end()) {
        Position boxNewPos = {newPos.x + dx, newPos.y + dy};
        
        if (walls.find(boxNewPos) == walls.end() && boxes.find(boxNewPos) == boxes.end()) {
            boxes.erase(newPos);
            boxes.insert(boxNewPos);
            playerPos = newPos;
            return true;
        }
        return false;
    }
    
    playerPos = newPos;
    return true;
}

bool SokobanGame::checkWin() {
    for (const auto& box : boxes) {
        if (targets.find(box) == targets.end()) {
            return false;
        }
    }
    return true;
}

void SokobanGame::play() {
    generateLevel();
    parseLevel();
    
    while (true) {
        drawGame();
        
        if (checkWin()) {
            std::cout << ColorCode::CYAN << "\n恭喜！你赢了！" << ColorCode::RESET << std::endl;
            std::cout << ColorCode::CYAN << "你用了 " << moves << " 步完成！" << ColorCode::RESET << std::endl;
            Utils::sleep(2);
            break;
        }
        
        std::cout << ColorCode::MAGENTA << "\n输入移动 (w/a/s/d) 或 q 退出: " << ColorCode::RESET;
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        char move = tolower(input[0]);
        
        if (move == 'q') break;
        
        int dx = 0, dy = 0;
        if (move == 'w') dy = -1;
        else if (move == 's') dy = 1;
        else if (move == 'a') dx = -1;
        else if (move == 'd') dx = 1;
        else continue;
        
        if (movePlayer(dx, dy)) {
            moves++;
        }
    }
}
