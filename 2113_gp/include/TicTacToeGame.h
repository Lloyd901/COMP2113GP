#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include "MiniGame.h"
#include <vector>
#include <string>

class TicTacToeGame : public MiniGame {
private:
    std::vector<std::vector<std::string>> board;
    
    void initBoard();
    void printBoard();
    bool isPositionTaken(int pos);
    void playerMove();
    void computerMove();
    bool checkWin(const std::string& symbol);
    bool isBoardFull();
    
public:
    TicTacToeGame();
    void play() override;
};

#endif // TICTACTOEGAME_H

