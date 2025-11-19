#ifndef HANGMANGAME_H
#define HANGMANGAME_H

#include "MiniGame.h"
#include <vector>
#include <string>

class HangmanGame : public MiniGame {
private:
    std::vector<std::string> hangmanImages;
    std::vector<std::string> words;
    
public:
    HangmanGame();
    void play() override;
};

#endif // HANGMANGAME_H

