#ifndef SCENE_START_H
#define SCENE_START_H

#include "shooter/Scene.h"

#include <SDL.h>

#include <string>

class SceneStart : public IScene {
public:
    SceneStart() = default;
    ~SceneStart() = default;

    virtual void initScene();
    virtual void cleanScene();

    virtual void updateScene(float deltaTime);
    virtual void renderScene();
    virtual void handleEventScene(SDL_Event* event);

private:
    void renderTextCentered(std::string text, float posY, bool isTitle);

private:
    float timer = 0.0f; // 计时器
};

#endif // SCENE_START_H