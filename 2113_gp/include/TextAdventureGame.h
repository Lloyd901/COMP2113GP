#ifndef TEXTADVENTUREGAME_H
#define TEXTADVENTUREGAME_H

#include "MiniGame.h"
#include <map>
#include <vector>
#include <string>

class TextAdventureGame : public MiniGame {
private:
    struct Room {
        std::string description;
        std::map<std::string, std::string> exits;
        std::string item;
        bool hasChest;
        bool chestLocked;
    };
    
    std::map<std::string, Room> rooms;
    std::vector<std::string> inventory;
    std::string currentRoom;
    
    void initializeRooms();
    void printSeparator();
    
public:
    TextAdventureGame();
    void play() override;
};

#endif // TEXTADVENTUREGAME_H

