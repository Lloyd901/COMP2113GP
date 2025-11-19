#include "TextAdventureGame.h"
#include "Utils.h"
#include "ColorCode.h"
#include <iostream>
#include <algorithm>

TextAdventureGame::TextAdventureGame() : MiniGame("文字冒险") {}

void TextAdventureGame::initializeRooms() {
    rooms["start"] = {
        "🕯️ 你在一个被闪烁烛光照亮的黑暗房间里。\n北边有一扇门，东边有一扇窗户。",
        {{"north", "corridor"}, {"east", "garden"}},
        "",
        false,
        false
    };
    
    rooms["corridor"] = {
        "🚪 你在一条狭长的走廊里。空气感觉很冷。\n南边有一扇门，地板上有一把闪闪发光的钥匙。",
        {{"south", "start"}},
        "key",
        false,
        false
    };
    
    rooms["garden"] = {
        "🌸 你在一个开满鲜花的美丽花园里。\n这里有一个上锁的箱子。西边的窗户通向室内。",
        {{"west", "start"}},
        "",
        true,
        true
    };
}

void TextAdventureGame::printSeparator() {
    std::cout << "\n" << std::string(50, '-') << "\n" << std::endl;
}

void TextAdventureGame::play() {
    initializeRooms();
    currentRoom = "start";
    inventory.clear();
    
    printSeparator();
    std::cout << ColorCode::MAGENTA << "欢迎来到迷你文字冒险游戏！" << ColorCode::RESET << std::endl;
    std::cout << ColorCode::CYAN << "\n如何游玩：" << ColorCode::RESET << std::endl;
    std::cout << "- 使用命令移动：north, south, east, west" << std::endl;
    std::cout << "- 收集物品：take" << std::endl;
    std::cout << "- 解锁物品：unlock" << std::endl;
    std::cout << "- 查看背包：inventory" << std::endl;
    std::cout << "- 退出游戏：quit" << std::endl;
    printSeparator();
    
    while (true) {
        Room& room = rooms[currentRoom];
        std::cout << ColorCode::GREEN << room.description << ColorCode::RESET << std::endl;
        
        std::cout << ColorCode::BLUE << "\n你想做什么？" << ColorCode::RESET;
        std::string command;
        std::getline(std::cin, command);
        command = Utils::trim(command);
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        if (command == "quit") {
            std::cout << ColorCode::CYAN << "感谢游玩！" << ColorCode::RESET << std::endl;
            break;
        } else if (command == "inventory") {
            printSeparator();
            if (inventory.empty()) {
                std::cout << ColorCode::YELLOW << "你的背包是空的。" << ColorCode::RESET << std::endl;
            } else {
                std::cout << ColorCode::CYAN << "你有：";
                for (const auto& item : inventory) {
                    std::cout << item << " ";
                }
                std::cout << ColorCode::RESET << std::endl;
            }
            printSeparator();
        } else if (room.exits.find(command) != room.exits.end()) {
            currentRoom = room.exits[command];
            std::cout << ColorCode::BLUE << "你移动到了 " << currentRoom << "！" << ColorCode::RESET << std::endl;
        } else if (command == "take") {
            if (!room.item.empty()) {
                inventory.push_back(room.item);
                std::cout << ColorCode::GREEN << "你拿起了 " << room.item << "。" << ColorCode::RESET << std::endl;
                room.item = "";
            } else {
                std::cout << ColorCode::YELLOW << "这里没有东西可拿！" << ColorCode::RESET << std::endl;
            }
        } else if (command == "unlock") {
            if (currentRoom == "garden") {
                bool hasKey = std::find(inventory.begin(), inventory.end(), "key") != inventory.end();
                if (hasKey && room.chestLocked) {
                    std::cout << ColorCode::GREEN << "你打开了箱子，找到了一顶金冠！你赢了！" << ColorCode::RESET << std::endl;
                    Utils::sleep(2);
                    break;
                } else if (!hasKey) {
                    std::cout << ColorCode::RED << "你需要一把钥匙来打开箱子！" << ColorCode::RESET << std::endl;
                } else {
                    std::cout << ColorCode::YELLOW << "箱子已经打开了！" << ColorCode::RESET << std::endl;
                }
            } else {
                std::cout << ColorCode::RED << "这里没有东西可以解锁！" << ColorCode::RESET << std::endl;
            }
        } else {
            std::cout << ColorCode::YELLOW << "无效命令！请输入：north, south, east, west, take, unlock, inventory, quit" << ColorCode::RESET << std::endl;
        }
    }
}

