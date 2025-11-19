#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "MiniGame.h"
#include <deque>

class SnakeGame : public MiniGame {
private:
    struct Position {
        int x, y;
        bool operator==(const Position& other) const;
    };
    
    static const int WIDTH = 40;
    static const int HEIGHT = 20;
    std::deque<Position> snake;
    Position food;
    char direction;
    int score;
    bool gameOver;
    
    void generateFood();
    bool isSnakePosition(const Position& pos);
    void drawGame();
    void moveSnake();
    
public:
    SnakeGame();
    void play() override;
};

#endif // SNAKEGAME_H

