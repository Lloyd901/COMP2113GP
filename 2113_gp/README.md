# 迷宫游戏 - 标准 C++ OOP 实现

## 项目结构

```
迷宫游戏_CPP版本/
├── include/          # 头文件目录
│   ├── ColorCode.h
│   ├── Utils.h
│   ├── MiniGame.h   # 游戏基类
│   ├── [游戏类].h   # 各个游戏的头文件
│   ├── MiniGameManager.h
│   ├── Maze.h
│   ├── Player.h
│   ├── MenuSystem.h
│   └── GameController.h
├── src/              # 实现文件目录
│   ├── Utils.cpp
│   ├── MiniGame.cpp
│   ├── [各个游戏类].cpp
│   ├── MiniGameManager.cpp
│   ├── Maze.cpp
│   ├── Player.cpp
│   ├── MenuSystem.cpp
│   └── GameController.cpp
├── main.cpp          # 主程序入口
└── Makefile          # 编译配置

```

## 编译运行

```bash
# 编译
make

# 运行
./maze_game

# 或一键编译运行
make run

# 清理
make clean
```

## OOP 特性

- **封装**：每个类都有明确的接口和实现分离
- **继承**：7个游戏类继承自 MiniGame 基类
- **多态**：通过虚函数实现游戏的动态调用

## 游戏内容

包含7个小游戏：
1. 井字棋
2. 猜数字
3. 石头剪刀布
4. Hangman猜词
5. 推箱子
6. 贪吃蛇
7. 文字冒险
