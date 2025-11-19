#ifndef GUESSNUMBERGAME_H
#define GUESSNUMBERGAME_H

#include "MiniGame.h"

class GuessNumberGame : public MiniGame {
public:
    GuessNumberGame();
    void play() override;
};

#endif // GUESSNUMBERGAME_H

