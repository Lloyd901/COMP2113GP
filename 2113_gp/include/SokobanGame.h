#ifndef SOKOBANGAME_H
#define SOKOBANGAME_H

#include "MiniGame.h"
#include <vector>
#include <set>
#include <string>

class SokobanGame : public MiniGame {
private:
    struct Position {
        int x, y;
        bool operator==(const Position& other) const;
        bool operator<(const Position& other) const;
    };
    
    std::vector<std::string> level;
    Position playerPos;
    std::set<Position> boxes;
    std::set<Position> targets;
    std::set<Position> walls;
    int moves;
    
    void parseLevel();
    void generateLevel();
    void drawGame();
    bool movePlayer(int dx, int dy);
    bool checkWin();
    
public:
    SokobanGame();
    void play() override;
};

#endif // SOKOBANGAME_H

