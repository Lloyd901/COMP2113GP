#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <map>
#include <string>

class MenuSystem {
public:
    struct GameSettings {
        int mazeSize;
        int minigameDensity;
        std::string playerAvatar;
    };
    
    enum class MenuChoice {
        MAZE_GAME,
        MINI_GAME,
        EXIT
    };
    
private:
    std::map<int, std::string> avatars;
    
    std::string selectAvatar();
    
public:
    MenuSystem();
    MenuChoice showMainMenu();
    GameSettings showMazeGameMenu();
    int showMiniGameMenu();
};

#endif // MENUSYSTEM_H

