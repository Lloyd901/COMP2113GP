#ifndef ROCKPAPERSCISSORSGAME_H
#define ROCKPAPERSCISSORSGAME_H

#include "MiniGame.h"

class RockPaperScissorsGame : public MiniGame {
private:
    char getComputerChoice();
    
public:
    RockPaperScissorsGame();
    void play() override;
};

#endif // ROCKPAPERSCISSORSGAME_H

