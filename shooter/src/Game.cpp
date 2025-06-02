#include "shooter/Game.h"

#include "shooter/MgrFont.h"
#include "shooter/MgrScene.h"
#include "shooter/MgrMusic.h"

Game::~Game() {
    cleanWinodws();

    quitSDL();
}

void Game::initGame() {
    initFPS();

    // resource
    initSDL();
    initWindow();

    // Mgr object
    FontMgr::getInstance().init();
    MusicMgr::getInstance().init();
    //
    SceneMgr::getInstance().init();
}

void Game::runGame() {
    while (isRunning) {
        SceneMgr::getInstance().run();
    }

    //
    
}

void Game::initSDL() {
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
}

void Game::quitSDL() {
    SDL_Quit();
}

void Game::initWindow() {
    // 创建窗口
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Window could not be created! SDL_Error: %s\n",
                     SDL_GetError());
        isRunning = false;
    }

    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Renderer could not be created! SDL_Error: %s\n",
                     SDL_GetError());
        isRunning = false;
    }
}

void Game::cleanWinodws() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::initFPS() {
    //
    frameTime = 1000 / FPS;
}
