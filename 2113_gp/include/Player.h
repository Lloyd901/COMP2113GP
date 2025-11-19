#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string avatar;
    int posY, posX;
    
public:
    Player(const std::string& av);
    
    std::string getAvatar() const;
    int getY() const;
    int getX() const;
    void setPosition(int y, int x);
};

#endif // PLAYER_H

