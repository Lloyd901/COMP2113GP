#include "SnakeGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>
#include <chrono>
#include <limits>

bool SnakeGame::Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

SnakeGame::SnakeGame() : MiniGame("贪吃蛇") {}

void SnakeGame::generateFood() {
    do {
        food = {Utils::getRandomInt(1, WIDTH - 2), Utils::getRandomInt(1, HEIGHT - 2)};
    } while (isSnakePosition(food));
}

bool SnakeGame::isSnakePosition(const Position& pos) {
    for (const auto& segment : snake) {
        if (segment == pos) return true;
    }
    return false;
}

void SnakeGame::drawGame() {
    Utils::clearScreen();
    std::cout << ColorCode::MAGENTA << "=== 贪吃蛇游戏 ===" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::MAGENTA << "分数: " << score << " | 用 w/a/s/d 控制方向" << ColorCode::RESET << std::endl;
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Position pos = {x, y};
            
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                std::cout << "#";
            } else if (pos == snake.front()) {
                std::cout << "O";
            } else if (isSnakePosition(pos)) {
                std::cout << "o";
            } else if (pos == food) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n目标：吃到5个食物就赢！当前：" << score << "/5" << std::endl;
}

void SnakeGame::moveSnake() {
    Position head = snake.front();
    Position newHead = head;
    
    if (direction == 'w') newHead.y--;
    else if (direction == 's') newHead.y++;
    else if (direction == 'a') newHead.x--;
    else if (direction == 'd') newHead.x++;
    
    if (newHead.x <= 0 || newHead.x >= WIDTH - 1 || 
        newHead.y <= 0 || newHead.y >= HEIGHT - 1) {
        gameOver = true;
        return;
    }
    
    if (isSnakePosition(newHead)) {
        gameOver = true;
        return;
    }
    
    snake.push_front(newHead);
    
    if (newHead == food) {
        score++;
        if (score >= 5) {
            gameOver = true;
            return;
        }
        generateFood();
    } else {
        snake.pop_back();
    }
}

void SnakeGame::play() {
    snake = {{WIDTH/2, HEIGHT/2}, {WIDTH/2-1, HEIGHT/2}, {WIDTH/2-2, HEIGHT/2}};
    direction = 'd';
    score = 0;
    gameOver = false;
    generateFood();
    
    std::cout << ColorCode::YELLOW << "贪吃蛇游戏开始！" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::YELLOW << "蛇会自动移动，使用 w/a/s/d 改变方向" << ColorCode::RESET << std::endl;
    std::cout << "按回车开始...";
    std::string dummy;
    std::getline(std::cin, dummy);
    
    // 启用非阻塞输入
    Utils::setNonBlockingInput(true);
    
    auto lastMoveTime = std::chrono::steady_clock::now();
    const int moveIntervalMs = 1000; // 每秒移动一次
    
    while (!gameOver) {
        drawGame();
        
        // 检查是否有键盘输入
        if (Utils::kbhit()) {
            char input = Utils::getch();
            char newDir = tolower(input);
            // 检查是否是有效的方向键，且不是相反方向
            if ((newDir == 'w' && direction != 's') ||
                (newDir == 's' && direction != 'w') ||
                (newDir == 'a' && direction != 'd') ||
                (newDir == 'd' && direction != 'a')) {
                direction = newDir;
            }
        }
        
        // 检查是否到了移动时间
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();
        
        if (elapsed >= moveIntervalMs) {
            moveSnake();
            lastMoveTime = currentTime;
        }
        
        // 短暂休眠以减少CPU使用率
        Utils::sleepMs(50);
    }
    
    // 恢复正常输入模式
    Utils::setNonBlockingInput(false);
    
    // 清空输入缓冲区中可能残留的字符
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    Utils::clearScreen();
    if (score >= 5) {
        std::cout << ColorCode::CYAN << "恭喜！你赢了！🎉" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::CYAN << "最终分数：" << score << ColorCode::RESET << std::endl;
    } else {
        std::cout << ColorCode::RED << "游戏结束！😢" << ColorCode::RESET << std::endl;
        std::cout << ColorCode::RED << "最终分数：" << score << "/5" << ColorCode::RESET << std::endl;
    }
    Utils::sleep(2);
}

