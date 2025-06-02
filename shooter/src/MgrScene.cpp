#include "shooter/MgrScene.h"
#include "shooter/Game.h"
#include "shooter/SceneStart.h"

void SceneMgr::init() {
    //
    // 初始化随机数生成器
    std::random_device rd;                                   // 获取真随机数作为种子
    gen = std::mt19937(rd());                                // 用种子初始化梅森旋转引擎
    dis = std::uniform_real_distribution<float>(0.0f, 1.0f); // 设置[0,1]均匀分布

    // currentScene = new SceneMain();
    currentScene = new SceneStart();
    currentScene->initScene();
}

void SceneMgr::run() {

    // game fps
    auto frameTime = Game::getInstance().getFrameTime();
    static float deltaTime = 0.0f;

    // start
    auto frameStart = SDL_GetTicks(); // 记录帧开始时间

    SDL_Event event;

    SceneHandleEvent(&event);
    SceneUpdate(deltaTime);
    SceneRender();

    auto frameEnd = SDL_GetTicks();    // 记录帧结束时间
    auto diff = frameEnd - frameStart; // 计算帧处理时间

    // 帧率限制和deltaTime计算
    if (diff < frameTime) {
        SDL_Delay(frameTime - diff);     // 如果处理太快，延迟一下
        deltaTime = frameTime / 1000.0f; // 转换为秒
    } else {
        deltaTime = diff / 1000.0f; // 如果处理较慢，使用实际时间
    }
}

void SceneMgr::changeScene(IScene *scene) {
    if (currentScene != nullptr) {
        currentScene->cleanScene();
        currentScene = nullptr;
    }

    currentScene = scene;
    currentScene->initScene();
}

void SceneMgr::SceneHandleEvent(SDL_Event *event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {

            // stop game
            Game::getInstance().setGameRunning(false);
        }
        currentScene->handleEventScene(event);
    }
}

void SceneMgr::SceneUpdate(float deltaTime) {
    currentScene->updateScene(deltaTime);
}

void SceneMgr::SceneRender() {
    auto renderer = Game::getInstance().getRenderer();

    // 清空
    SDL_RenderClear(renderer);
    // 渲染
    currentScene->renderScene();
    // 显示更新
    SDL_RenderPresent(renderer);
}
