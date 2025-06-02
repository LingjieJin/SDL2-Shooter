#ifndef SC_ENEMY_H
#define SC_ENEMY_H

#include "shooter/Scene.h"

#include <SDL.h>

#include <list>

class EnemyObject {
public:
    EnemyObject() = default;
    ~EnemyObject() = default;

    // 拷贝构造函数
    EnemyObject(const EnemyObject &enemy) {
        this->texture = enemy.texture;
        this->position = enemy.position;
        this->width = enemy.width;
        this->height = enemy.height;
        this->speed = enemy.speed;
        this->coolDown = enemy.coolDown;
        this->lastShootTime = enemy.lastShootTime;
        this->currentHealth = enemy.currentHealth;
    }

public:
    SDL_Texture *texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 100; // 敌机移动速度

    Uint32 coolDown = 2000;   // 发射冷却时间（1秒）
    Uint32 lastShootTime = 0; // 上次发射时间

    int currentHealth = 2; // 敌机初始生命值为2
};

class EnemySceneContent : public ISceneContent {
public:
    void initContent() override;
    void renderContent() override;
    void cleanContent() override;

public:
    EnemyObject &getEnemyTemplate_1() {
        return enemyTemplate_1;
    }
    EnemyObject &getEnemyTemplate_2() {
        return enemyTemplate_2;
    }

    std::list<EnemyObject *> &getEnemies() {
        return enemies;
    }

    std::list<EnemyObject *> *getEnemiesPtr() {
        return &enemies;
    }

private:
    // 敌机相关成员
    EnemyObject enemyTemplate_1;      // 敌机模板
    EnemyObject enemyTemplate_2;      // 敌机模板
    std::list<EnemyObject *> enemies; // 存储活动敌机的列表
};

#endif // SC_ENEMY_H