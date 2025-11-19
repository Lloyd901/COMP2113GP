#ifndef MAZE_H
#define MAZE_H

#include "MiniGameManager.h"
#include <vector>
#include <string>
#include <utility>

class Maze {
private:
    int width, height;
    std::vector<std::vector<std::string>> grid;
    std::string playerAvatar;
    int minigameDensity;
    
    void generateMaze();
    void addMiniGames();
    
public:
    Maze(int w, int h, const std::string& avatar, int density);
    void print() const;
    bool move(int& playerY, int& playerX, char direction, MiniGameManager& gameManager);
    std::pair<int, int> getStartPosition() const;
};

#endif // MAZE_H

