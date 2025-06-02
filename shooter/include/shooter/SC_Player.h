#ifndef SC_PLAYER_H
#define SC_PLAYER_H

#include "shooter/Scene.h"

#include <SDL.h>

class PlayerObject {
public:
    PlayerObject() = default;
    ~PlayerObject() = default;

public:
    SDL_Texture *texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 200; // 每秒移动200像素
    //
    Uint32 coolDown = 500;    // 射击冷却时间（毫秒）
    Uint32 lastShootTime = 0; // 上次射击的时间

    int currentHealth = 3; // 玩家初始生命值
    int maxHealth = 10;    // 玩家最大生命值
    bool isDead = false;
};

class PlayerSceneContent : public ISceneContent {
public:
    void initContent() override;
    void renderContent() override;
    void cleanContent() override;

    //
    PlayerObject &getPlayerRef() {
        return player;
    }

private:
    PlayerObject player;
};

#endif // SC_PLAYER_H