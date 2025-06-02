#include "shooter/SC_Enemy.h"
#include "shooter/Game.h"

#include "shooter/Resource.h"

#include <SDL_image.h>

void EnemySceneContent::initContent() {
    //
    Game &game = Game::getInstance();

    // 初始化敌机模板
    enemyTemplate_1.texture =
        IMG_LoadTexture(game.getRenderer(), enemy_img_1_path.c_str());
    SDL_QueryTexture(enemyTemplate_1.texture, NULL, NULL, &enemyTemplate_1.width,
                     &enemyTemplate_1.height);
    enemyTemplate_1.width /= 4;
    enemyTemplate_1.height /= 4;

    enemyTemplate_2.texture =
        IMG_LoadTexture(game.getRenderer(), enemy_img_2_path.c_str());
    SDL_QueryTexture(enemyTemplate_2.texture, NULL, NULL, &enemyTemplate_2.width,
                     &enemyTemplate_2.height);
    enemyTemplate_2.width /= 4;
    enemyTemplate_2.height /= 4;
}

void EnemySceneContent::renderContent() {
    //
    Game &game = Game::getInstance();
    //
    for (auto enemy : enemies) {
        SDL_Rect enemyRect = {static_cast<int>(enemy->position.x),
                              static_cast<int>(enemy->position.y), enemy->width,
                              enemy->height};
        SDL_RenderCopy(game.getRenderer(), enemy->texture, NULL, &enemyRect);
    }
}

void EnemySceneContent::cleanContent() {
    // 清理敌机
    for (auto &enemy : enemies) {
        if (enemy != nullptr) {
            delete enemy;
        }
    }
    enemies.clear();

    if (enemyTemplate_1.texture != nullptr) {
        SDL_DestroyTexture(enemyTemplate_1.texture);
    }

    if (enemyTemplate_2.texture != nullptr) {
        SDL_DestroyTexture(enemyTemplate_2.texture);
    }
}
