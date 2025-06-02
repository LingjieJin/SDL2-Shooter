#include "shooter/SceneStart.h"
#include "shooter/SceneGame.h"

#include "shooter/MgrMusic.h"
#include "shooter/MgrFont.h"
#include "shooter/MgrScene.h"

#include "shooter/Game.h"

#include <string>

void SceneStart::initScene() {
    // 播放背景音乐
    MusicMgr::getInstance().soundBgm();
}

void SceneStart::cleanScene() {

}

void SceneStart::updateScene(float deltaTime) {
    timer += deltaTime;
    if (timer > 1.0f) {
        timer -= 1.0f;
    }
}

void SceneStart::renderScene() {
    // 渲染标题文字
    std::string titleText = "SDL太空战机";
    renderTextCentered(titleText, 0.4, true);

    // 渲染普通文字
    if (timer < 0.5f) {
        std::string instructions = "按 J 键开始游戏";
        renderTextCentered(instructions, 0.8, false);
    }
}

void SceneStart::handleEventScene(SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.scancode == SDL_SCANCODE_J) {
            // 
            auto sceneMain = new SceneGame();
            SceneMgr::getInstance().changeScene(sceneMain);
        }
    }
}

void SceneStart::renderTextCentered(std::string text, float posY, bool isTitle) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface;
    if (isTitle) {
        surface = TTF_RenderUTF8_Solid(FontMgr::getInstance().getTitleFontPtr(), text.c_str(), color);
    } else {
        surface = TTF_RenderUTF8_Solid(FontMgr::getInstance().getTextFontPtr(), text.c_str(), color);
    }

    Game& game = Game::getInstance();
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.getRenderer(), surface);
    int y = static_cast<int>((game.getWindowHeight() - surface->h) * posY);
    SDL_Rect rect = {game.getWindowWidth() / 2 - surface->w / 2,
                     y,
                     surface->w,
                     surface->h};
    SDL_RenderCopy(game.getRenderer(), texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
