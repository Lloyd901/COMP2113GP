#include "Maze.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>
#include <functional>
#include <random>
#include <algorithm>

Maze::Maze(int w, int h, const std::string& avatar, int density) 
    : width(w), height(h), playerAvatar(avatar), minigameDensity(density) {
    generateMaze();
    addMiniGames();
}

void Maze::generateMaze() {
    int rows = (height * 2) + 1;
    int cols = (width * 2) + 1;
    grid.assign(rows, std::vector<std::string>(cols, "🔲"));
    
    std::vector<std::pair<int, int>> moves = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};
    
    std::function<void(int, int)> carvePassages = [&](int x, int y) {
        auto shuffledMoves = moves;
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(shuffledMoves.begin(), shuffledMoves.end(), g);
        
        for (auto& move : shuffledMoves) {
            int newX = x + move.first;
            int newY = y + move.second;
            
            if (newX > 0 && newX < cols - 1 && newY > 0 && newY < rows - 1 && grid[newY][newX] == "🔲") {
                grid[y + move.second / 2][x + move.first / 2] = "  ";
                grid[newY][newX] = "  ";
                carvePassages(newX, newY);
            }
        }
    };
    
    carvePassages(1, 1);
    grid[1][1] = playerAvatar;
    grid[rows - 2][cols - 2] = "🏁";
}

void Maze::addMiniGames() {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == "  ") {
                int n = Utils::getRandomInt(1, 20);
                if (n <= minigameDensity) {
                    grid[i][j] = "!!";
                }
            }
        }
    }
}

void Maze::print() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == "🔲") {
                std::cout << ColorCode::GREEN << cell << ColorCode::RESET;
            } else if (cell == "!!") {
                std::cout << ColorCode::RED << cell << ColorCode::RESET;
            } else {
                std::cout << ColorCode::YELLOW << cell << ColorCode::RESET;
            }
        }
        std::cout << std::endl;
    }
}

bool Maze::move(int& playerY, int& playerX, char direction, MiniGameManager& gameManager) {
    int newY = playerY, newX = playerX;
    
    switch (direction) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return false;
    }
    
    if (newY < 0 || newY >= (int)grid.size() || newX < 0 || newX >= (int)grid[0].size()) {
        return false;
    }
    
    if (grid[newY][newX] == "🔲") {
        std::cout << ColorCode::RED << "哎呀！你撞墙了" << ColorCode::RESET << std::endl;
        return false;
    }
    
    if (grid[newY][newX] == "🏁") {
        grid[playerY][playerX] = "  ";
        grid[newY][newX] = playerAvatar;
        playerY = newY;
        playerX = newX;
        return true;
    }
    
    if (grid[newY][newX] == "!!") {
        grid[playerY][playerX] = "  ";
        grid[newY][newX] = playerAvatar;
        playerY = newY;
        playerX = newX;
        print();
        std::cout << ColorCode::YELLOW << "小游戏时间！" << ColorCode::RESET << std::endl;
        Utils::sleepMs(1500);
        gameManager.playRandomGame();
        return false;
    }
    
    grid[playerY][playerX] = "  ";
    grid[newY][newX] = playerAvatar;
    playerY = newY;
    playerX = newX;
    return false;
}

std::pair<int, int> Maze::getStartPosition() const {
    return {1, 1};
}
