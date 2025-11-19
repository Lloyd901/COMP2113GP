# Makefile for Maze Game - Standard OOP Structure

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
TARGET = maze_game

# Source files
SOURCES = src/Utils.cpp \
          src/MiniGame.cpp \
          src/GuessNumberGame.cpp \
          src/RockPaperScissorsGame.cpp \
          src/TicTacToeGame.cpp \
          src/HangmanGame.cpp \
          src/SokobanGame.cpp \
          src/SnakeGame.cpp \
          src/TextAdventureGame.cpp \
          src/MiniGameManager.cpp \
          src/Maze.cpp \
          src/Player.cpp \
          src/MenuSystem.cpp \
          src/GameController.cpp \
          main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "编译完成！可执行文件：$(TARGET)"

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run program
run: $(TARGET)
	./$(TARGET)

# Debug version
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -DDEBUG -Iinclude
debug: clean $(TARGET)
	@echo "调试版本编译完成"

# Clean
clean:
	rm -f $(TARGET) $(OBJECTS)
	@echo "清理完成"

# Display help
help:
	@echo "可用的 make 目标："
	@echo "  make          - 编译程序"
	@echo "  make run      - 编译并运行程序"
	@echo "  make debug    - 编译调试版本"
	@echo "  make clean    - 清理编译生成的文件"
	@echo "  make help     - 显示此帮助信息"

.PHONY: all run debug clean help
