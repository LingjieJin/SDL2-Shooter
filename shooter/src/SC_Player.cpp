#include "shooter/SC_Player.h"

#include "shooter/Game.h"
#include "shooter/Resource.h"

#include <SDL_image.h>

void PlayerSceneContent::initContent() {
    Game &game = Game::getInstance();

    player.texture = IMG_LoadTexture(game.getRenderer(), player_img_path.c_str());
    if (player.texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load player texture: %s",
                     SDL_GetError());
    }
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = game.getWindowWidth() / 2 - player.width / 2;
    player.position.y = game.getWindowHeight() - player.height;
}

void PlayerSceneContent::renderContent() {
    Game &game = Game::getInstance();

    if (!player.isDead) {
        SDL_Rect playerRect = {static_cast<int>(player.position.x),
                               static_cast<int>(player.position.y), player.width,
                               player.height};
        SDL_RenderCopy(game.getRenderer(), player.texture, NULL,
                       &playerRect);
    }


}

void PlayerSceneContent::cleanContent() {
    if (player.texture != nullptr) {
        SDL_DestroyTexture(player.texture);
    }
}
