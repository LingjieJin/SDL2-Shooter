#include "shooter/SC_Bullet.h"

#include "shooter/Resource.h"

#include "shooter/Game.h"

#include <SDL_image.h>

void BulletOfPlayerSceneContent::initContent() {
    //
    Game &game = Game::getInstance();
    // 初始化子弹模板
    m_template.texture =
        IMG_LoadTexture(game.getRenderer(), player_bullet_img_path.c_str());
    SDL_QueryTexture(m_template.texture, NULL, NULL,
                     &m_template.width, &m_template.height);
    m_template.width /= 4;
    m_template.height /= 4;
}

void BulletOfPlayerSceneContent::renderContent() {
    //
    Game &game = Game::getInstance();

    //
    for (auto bullet : m_bulletList) {
        SDL_Rect bulletRect = {static_cast<int>(bullet->position.x),
                               static_cast<int>(bullet->position.y),
                               bullet->width, bullet->height};
        SDL_RenderCopy(game.getRenderer(), bullet->texture, NULL,
                       &bulletRect);
    }
}

void BulletOfPlayerSceneContent::cleanContent() {
    // 清理子弹
    for (auto &bullet : m_bulletList) {
        if (bullet != nullptr) {
            delete bullet;
        }
    }
    m_bulletList.clear();

    // 清理子弹纹理
    if (m_template.texture != nullptr) {
        SDL_DestroyTexture(m_template.texture);
    }
}


/**************************************/
// 敌机子弹
/**************************************/

void BulletOfEnemySceneContent::initContent() {
    //
    Game &game = Game::getInstance();
    // 初始化敌机子弹模板
    m_template.texture = IMG_LoadTexture(
        game.getRenderer(), bulletEnemy_img_path.c_str());
    SDL_QueryTexture(m_template.texture, NULL, NULL,
                     &m_template.width, &m_template.height);
    m_template.width /= 4;
    m_template.height /= 4;
}

void BulletOfEnemySceneContent::renderContent() {
    //
    Game &game = Game::getInstance();
    //
    for (auto bullet : m_bulletList) {
        BulletEnemy *bulletEnemy = static_cast<BulletEnemy *>(bullet);

        SDL_Rect Rect = {static_cast<int>(bulletEnemy->position.x),
                         static_cast<int>(bulletEnemy->position.y),
                         bulletEnemy->width, bulletEnemy->height};

        // 计算子弹旋转角度（从弧度转换为角度，并调整为正确的方向）
        float angle =
            atan2(bulletEnemy->direction.y, bulletEnemy->direction.x) * 180 / M_PI - 90;

        // 使用带旋转参数的渲染函数
        SDL_RenderCopyEx(game.getRenderer(),
                         bulletEnemy->texture, NULL, &Rect, angle, NULL,
                         SDL_FLIP_NONE);
    }
}

void BulletOfEnemySceneContent::cleanContent() {
    // 清理敌机子弹
    for (auto &bullet : m_bulletList) {
        if (bullet != nullptr) {
            delete bullet;
        }
    }
    m_bulletList.clear();

    if (m_template.texture != nullptr) {
        SDL_DestroyTexture(m_template.texture);
    }
}
