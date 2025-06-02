#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class IScene{
public:
    virtual void initScene() = 0;
    virtual void cleanScene() = 0;

    virtual void updateScene(float deltaTime) = 0;
    virtual void renderScene() = 0;
    virtual void handleEventScene(SDL_Event* event) = 0;
};

class ISceneContent {
public:
    virtual void initContent() = 0;
    virtual void renderContent() = 0;
    virtual void cleanContent() = 0;
};

#endif // SCENE_H