#include "shooter/MgrFont.h"

#include "shooter/Game.h"

void FontMgr::init() {
    // SDL_TTF初始化
    if (TTF_Init() != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "SDL_TTF could not initialize! SDL_TTF Error: %s\n",
                     TTF_GetError());
        Game::getInstance().setGameRunning(false);
    }

    //
    titleFont = TTF_OpenFont("../assets/font/VonwaonBitmap-16px.ttf", 64);
    textFont = TTF_OpenFont("../assets/font/VonwaonBitmap-16px.ttf", 32);
    if (titleFont == nullptr || textFont == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_OpenFont: %s\n", TTF_GetError());
    }
}