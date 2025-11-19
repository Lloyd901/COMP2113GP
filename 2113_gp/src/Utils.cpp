#include "Utils.h"
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <cctype>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
    #include <conio.h>
#else
    #define CLEAR_SCREEN "clear"
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
#endif

void Utils::clearScreen() {
    system(CLEAR_SCREEN);
}

void Utils::sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Utils::sleepMs(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int Utils::getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

std::string Utils::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

bool Utils::isDigit(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool Utils::isAlpha(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalpha(c)) return false;
    }
    return true;
}

char Utils::toUpper(char c) {
    return toupper(c);
}

std::string Utils::toUpperStr(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

#ifdef _WIN32
bool Utils::kbhit() {
    return _kbhit();
}

char Utils::getch() {
    return _getch();
}

void Utils::setNonBlockingInput(bool enable) {
    // Windows implementation (if needed)
}
#else
bool Utils::kbhit() {
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);

    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}

char Utils::getch() {
    char buf = 0;
    if (read(STDIN_FILENO, &buf, 1) > 0) {
        return buf;
    }
    return 0;
}

void Utils::setNonBlockingInput(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}
#endif

