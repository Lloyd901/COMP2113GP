#ifndef MINIGAME_H
#define MINIGAME_H

#include <string>

class MiniGame {
protected:
    std::string gameName;
    
public:
    MiniGame(const std::string& name);
    virtual ~MiniGame() = default;
    
    virtual void play() = 0;
    
    std::string getGameName() const;
};

#endif // MINIGAME_H

