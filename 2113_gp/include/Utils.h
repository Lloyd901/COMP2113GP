#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static void clearScreen();
    static void sleep(int seconds);
    static void sleepMs(int milliseconds);
    static int getRandomInt(int min, int max);
    static std::string trim(const std::string& str);
    static bool isDigit(const std::string& str);
    static bool isAlpha(const std::string& str);
    static char toUpper(char c);
    static std::string toUpperStr(const std::string& str);
    static bool kbhit();
    static char getch();
    static void setNonBlockingInput(bool enable);
};

#endif // UTILS_H

