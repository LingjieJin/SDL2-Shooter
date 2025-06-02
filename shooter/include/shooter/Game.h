#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {
public:
    static Game &getInstance() {
        static Game instance;
        return instance;
    }
    ~Game();

    void initGame();

    void runGame();

public:
    SDL_Window *getWindow() {
        return window;
    }
    SDL_Renderer *getRenderer() {
        return renderer;
    }
    int getWindowWidth() {
        return windowWidth;
    }
    int getWindowHeight() {
        return windowHeight;
    }

    Uint32 getFrameTime() {
        return frameTime;
    }

    void setGameRunning(bool status) {
        isRunning = status;
    }

    bool getGameRunning() {
        return isRunning;
    }

private:
    Game() = default;
    // 删除拷贝与赋值构造函数
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    //
    void initSDL();
    void quitSDL();

    void initWindow();
    void cleanWinodws();

    void initFPS();

private:
    //
    bool isRunning = true;
    int FPS = 60;     // 目标帧率
    Uint32 frameTime; // 每帧的目标时间（毫秒）

    //
    int finalScore = 0;

    // game windows
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int windowWidth = 600;
    int windowHeight = 800;
};

#endif // GAME_H