#ifndef MINIGAMEMANAGER_H
#define MINIGAMEMANAGER_H

#include "MiniGame.h"
#include <vector>
#include <memory>
#include <string>

class MiniGameManager {
private:
    std::vector<std::unique_ptr<MiniGame>> games;
    
public:
    MiniGameManager();
    void playRandomGame();
    void playGameByIndex(int index);
    int getGameCount() const;
    std::string getGameName(int index) const;
};

#endif // MINIGAMEMANAGER_H

