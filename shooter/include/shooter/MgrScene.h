#ifndef SCENE_MGR_H
#define SCENE_MGR_H

#include <SDL.h>

#include "shooter/Scene.h"

#include <list>
#include <random>

class SceneMgr {
public:
    static SceneMgr &getInstance() {
        static SceneMgr instance;
        return instance;
    }
    ~SceneMgr() = default;

    void init();
    void run();
    void changeScene(IScene *scene);

public:
    std::uniform_real_distribution<float> &getDis() {
        return dis;
    }

private:
    void SceneHandleEvent(SDL_Event *event);
    void SceneUpdate(float deltaTime);
    void SceneRender();

private:
    SceneMgr() = default;
    // 删除拷贝与赋值构造函数
    SceneMgr(const SceneMgr &) = delete;
    SceneMgr &operator=(const SceneMgr &) = delete;
    //
    IScene *currentScene = nullptr;
    //
    // 随机数相关成员
    std::mt19937 gen;                          // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器
};

#endif // SCENE_MGR_H