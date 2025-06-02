#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "shooter/Scene.h"

#include <list>
#include <map>
#include <unordered_map>
#include <string>


class SceneGame : public IScene {
public:
    SceneGame() = default;
    ~SceneGame() = default;

    virtual void initScene();
    virtual void cleanScene();
    
    virtual void updateScene(float deltaTime);
    virtual void renderScene();
    virtual void handleEventScene(SDL_Event* event);

    //
    void keyboardControl(float deltaTime);
    void updateBulletOfPlayer(float deltaTime);
    void genEnemy();
    void updateEnemys(float deltaTime);

private:

    std::list<ISceneContent*> m_sceneContentList;
    std::unordered_map<std::string, ISceneContent*> m_sceneContentMap;
};

#endif // SCENE_GAME_H