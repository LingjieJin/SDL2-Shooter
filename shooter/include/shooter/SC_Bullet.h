#ifndef SC_BULLET_H
#define SC_BULLET_H

#include "shooter/Scene.h"
#include "shooter/SC_Player.h"
#include "shooter/SC_Enemy.h"

#include <SDL.h>

#include <list>

class BulletObj {
public:
    SDL_Texture *texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 400; // 子弹移动速度
    int damage = 0;  // 子弹伤害值为1
};

class BulletPlayer : public BulletObj {
public:
    SDL_Texture *texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 400; // 子弹移动速度
    int damage = 2;  // 玩家子弹伤害值为1

public:
    static BulletPlayer *genBulletFromPlayer(PlayerObject& player, BulletPlayer& bulletTemplate) {
        // 创建新子弹
        BulletPlayer *bullet = new BulletPlayer(bulletTemplate);
        // 定位在飞机顶部中央
        bullet->position.x = player.position.x + player.width / 2 - bullet->width / 2;
        bullet->position.y = player.position.y;

        return bullet;
    }
};

class BulletEnemy : public BulletObj {
public:
    SDL_Texture *texture = nullptr;
    SDL_FPoint position = {0, 0};
    SDL_FPoint direction = {0, 0}; // 子弹方向向量
    int width = 0;
    int height = 0;
    int speed = 200;
    int damage = 1; // 敌机子弹伤害值为1
public:
    static BulletEnemy *genBulletFromEnemyToPlayer(EnemyObject &enemy, PlayerObject &player, BulletEnemy &bulletTemplate) {
        // 创建新子弹
        BulletEnemy *bullet = new BulletEnemy(bulletTemplate);
        bullet->texture = bulletTemplate.texture;

        // 设置子弹初始位置（从敌机中央发射）
        bullet->position.x = enemy.position.x + enemy.width / 2 - bullet->width / 2;
        bullet->position.y = enemy.position.y + enemy.height / 2 - bullet->height / 2;

        // 计算子弹飞向玩家的方向
        bullet->direction = getDirection(enemy, player);
        return bullet;
    }

    static SDL_FPoint getDirection(EnemyObject &enemy, PlayerObject &player) {
        // 计算从敌机中心到玩家中心的向量
        auto x = (player.position.x + player.width / 2) - (enemy.position.x + enemy.width / 2);
        auto y = (player.position.y + player.height / 2) - (enemy.position.y + enemy.height / 2);

        // 计算向量长度
        auto length = sqrt(x * x + y * y);

        // 归一化向量
        x /= length;
        y /= length;

        return SDL_FPoint{x, y};
    }
};

class BulletOfPlayerSceneContent : public ISceneContent {
public:
    void initContent() override;
    void renderContent() override;
    void cleanContent() override;

public:
    BulletPlayer &getBulletTemplate() {
        return m_template;
    }

    std::list<BulletPlayer *> &getBulletList() {
        return m_bulletList;
    }

private:
    // 创建子弹模板
    BulletPlayer m_template;
    // 存储活动子弹的列表
    std::list<BulletPlayer *> m_bulletList;
};

class BulletOfEnemySceneContent : public ISceneContent {
public:
    void initContent() override;
    void renderContent() override;
    void cleanContent() override;

public:
    BulletEnemy &getBulletTemplate() {
        return m_template;
    }

    std::list<BulletEnemy *> &getBulletList() {
        return m_bulletList;
    }

private:
    // 创建子弹模板
    BulletEnemy m_template;
    // 存储敌机子弹的列表
    std::list<BulletEnemy *> m_bulletList;
};

#endif // SC_BULLET_H