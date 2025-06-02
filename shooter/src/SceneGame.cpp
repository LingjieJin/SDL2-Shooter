#include "shooter/SceneGame.h"
#include "shooter/Game.h"

#include <shooter/MgrScene.h>
#include "shooter/MgrMusic.h"

#include "shooter/SC_Player.h"
#include "shooter/SC_Enemy.h"
#include "shooter/SC_Bullet.h"

void SceneGame::initScene() {
    //
    PlayerSceneContent *player_sc = new PlayerSceneContent();
    m_sceneContentList.push_back(player_sc);
    m_sceneContentMap["player"] = player_sc;

    //
    BulletOfPlayerSceneContent *bulletOfPlayer_sc = new BulletOfPlayerSceneContent();
    m_sceneContentList.push_back(bulletOfPlayer_sc);
    m_sceneContentMap["bulletOfPlayer"] = bulletOfPlayer_sc;

    //
    EnemySceneContent *enemy_sc = new EnemySceneContent();
    m_sceneContentList.push_back(enemy_sc);
    m_sceneContentMap["enemy"] = enemy_sc;

    //
    BulletOfEnemySceneContent *bulletOfEnemy_sc = new BulletOfEnemySceneContent();
    m_sceneContentList.push_back(bulletOfEnemy_sc);
    m_sceneContentMap["bulletOfEnemy"] = bulletOfEnemy_sc;

    //
    for (auto sc : m_sceneContentList) {
        sc->initContent();
    }
}

void SceneGame::cleanScene() {
    for (auto sc : m_sceneContentList) {
        sc->cleanContent();
    }

    //
    m_sceneContentList.clear();
    m_sceneContentMap.clear();
}

void SceneGame::updateScene(float deltaTime) {
    keyboardControl(deltaTime);

    // 更新子弹
    updateBulletOfPlayer(deltaTime);
    //
    updateEnemys(deltaTime);
    
}

void SceneGame::renderScene() {
    for (auto sc : m_sceneContentList) {
        sc->renderContent();
    }
}

void SceneGame::handleEventScene(SDL_Event * /*event*/) {
}

void SceneGame::keyboardControl(float deltaTime) {
    Game &game = Game::getInstance();

    // 获取玩家场景
    auto playerSC = dynamic_cast<PlayerSceneContent *>(m_sceneContentMap.at("player"));
    PlayerObject &playerObj = playerSC->getPlayerRef();

    auto keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_UP]) {
        playerObj.position.y -= deltaTime * playerObj.speed; // 基于时间的移动
    }
    if (keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN]) {
        playerObj.position.y += deltaTime * playerObj.speed;
    }
    if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) {
        playerObj.position.x -= deltaTime * playerObj.speed;
    }
    if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) {
        playerObj.position.x += deltaTime * playerObj.speed;
    }

    // 限制飞机的移动范围
    if (playerObj.position.x < 0) {
        playerObj.position.x = 0;
    }
    if (playerObj.position.x > game.getWindowWidth() - playerObj.width) {
        playerObj.position.x = (float)game.getWindowWidth() - playerObj.width;
    }
    if (playerObj.position.y < 0) {
        playerObj.position.y = 0;
    }
    if (playerObj.position.y > game.getWindowHeight() - playerObj.height) {
        playerObj.position.y = (float)game.getWindowHeight() - playerObj.height;
    }

    // 控制子弹发射
    // 获取玩家子弹场景内容
    BulletOfPlayerSceneContent &bulletOfPlayerSC = dynamic_cast<BulletOfPlayerSceneContent &>(*m_sceneContentMap.at("bulletOfPlayer"));

    if (keyboardState[SDL_SCANCODE_J] || keyboardState[SDL_SCANCODE_SPACE]) {
        auto currentTime = SDL_GetTicks();
        if (currentTime - playerObj.lastShootTime > playerObj.coolDown) {
            BulletPlayer *bullet = BulletPlayer::genBulletFromPlayer(playerObj, bulletOfPlayerSC.getBulletTemplate());
            bulletOfPlayerSC.getBulletList().push_back(bullet);

            playerObj.lastShootTime = currentTime;
        }
    }
}

void SceneGame::updateBulletOfPlayer(float deltaTime) {
    //
    // 获取玩家子弹场景内容
    BulletOfPlayerSceneContent &bulletOfPlayerSC = dynamic_cast<BulletOfPlayerSceneContent &>(*m_sceneContentMap.at("bulletOfPlayer"));

    //
    int margin = 32; // 子弹超出屏幕外边界的距离
    for (auto it = bulletOfPlayerSC.getBulletList().begin(); it != bulletOfPlayerSC.getBulletList().end();) {
        // 子弹
        auto bulletPlayer = *it;
        // 更新子弹位置
        bulletPlayer->position.y -= bulletPlayer->speed * deltaTime;

        // 检查子弹是否超出屏幕
        if (bulletPlayer->position.y + margin < 0) {
            delete bulletPlayer;
            it = bulletOfPlayerSC.getBulletList().erase(it);
        } else {
            bool hit = false;
            //   auto enemies = ptr_sceneMain->getSceneEnemy()->getEnemies();
            //   for (auto enemy : enemies) {

            //     SDL_Rect enemyRect = {static_cast<int>(enemy->position.x),
            //                           static_cast<int>(enemy->position.y), enemy->width,
            //                           enemy->height};

            //     SDL_Rect projectileRect = {static_cast<int>(bulletPlayer->position.x),
            //                                static_cast<int>(bulletPlayer->position.y),
            //                                bulletPlayer->width, bulletPlayer->height};

            //     if (SDL_HasIntersection(&enemyRect, &projectileRect)) {
            //       enemy->currentHealth -= bulletPlayer->damage;
            //       delete bulletPlayer;
            //       it = bulletOfPlayerSC.getBulletList().erase(it);
            //       hit = true;

            //       // 击中音效
            //       ptr_sceneMain->getMusicPlayer()->soundHit();

            //       break;
            //     }
            //   }

            if (!hit) {
                ++it;
            }
        }
    }
}

void SceneGame::updateEnemys(float deltaTime) {
    Game &game = Game::getInstance();
    // 获取玩家场景
    auto playerSC = dynamic_cast<PlayerSceneContent *>(m_sceneContentMap.at("player"));
    PlayerObject &playerObj = playerSC->getPlayerRef();
    //
    auto enemySC = dynamic_cast<EnemySceneContent &>(*m_sceneContentMap.at("enemy"));

    BulletOfEnemySceneContent &bulletOfEnemySC = dynamic_cast<BulletOfEnemySceneContent &>(*m_sceneContentMap.at("bulletOfEnemy"));

    auto enemylist = enemySC.getEnemiesPtr();
    // 生成敌机
    genEnemy();

    auto currentTime = SDL_GetTicks();
    // 更新敌机
    for (auto it = enemylist->begin(); it != enemylist->end();) {
        auto enemy = *it;

        // 更新敌机位置
        enemy->position.y += enemy->speed * deltaTime;

        // 检查敌机是否飞出屏幕底部
        if (enemy->position.y > game.getWindowHeight()) {
            // delete enemy;
            it = enemylist->erase(it);
        } else {
            // 检查冷却时间，决定是否发射子弹
            if (currentTime - enemy->lastShootTime > enemy->coolDown) {
                // 发射子弹
                BulletEnemy *bullet = BulletEnemy::genBulletFromEnemyToPlayer(*enemy, playerObj, bulletOfEnemySC.getBulletTemplate());
                bulletOfEnemySC.getBulletList().push_back(bullet);
                enemy->lastShootTime = currentTime;

                // 播放音乐
                MusicMgr::getInstance().soundShootEnemy();
            }

            if (enemy->currentHealth <= 0) {
                // // 爆炸敌机
                // enemyExplode(enemy);
                it = enemylist->erase(it);
            } else {
                ++it;
            }
        }
    }
}

void SceneGame::genEnemy() {
    //
    Game &game = Game::getInstance();
    EnemySceneContent &enemySC = dynamic_cast<EnemySceneContent &>(*m_sceneContentMap.at("enemy"));

    // 生成敌机
    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis = SceneMgr::getInstance().getDis();
    // 利用随机数决定是否生成敌机（每帧约1/60的概率）
    if (dis(gen) > 1 / 60.0f) {
        return;
    }

    // 创建新敌机
    std::uniform_int_distribution<int> typeDist(0, 1);
    int enemyType = typeDist(gen);
    EnemyObject *enemy = nullptr;
    if (enemyType == 0) {
        enemy = new EnemyObject(enemySC.getEnemyTemplate_1());
    } else if (enemyType == 1) {
        enemy = new EnemyObject(enemySC.getEnemyTemplate_2());
    } else {
        // 如果随机数不在0和1之间，则使用默认敌机模板
        enemy = new EnemyObject(enemySC.getEnemyTemplate_1());
    }

    std::uniform_real_distribution<float> speedDist(150.0f, 300.0f);
    enemy->speed = speedDist(gen);

    std::uniform_real_distribution<float> scaleDist(0.8f, 1.2f);
    float scale = scaleDist(gen);
    enemy->width *= scale;
    enemy->height *= scale;

    // 利用随机数决定敌机的水平位置
    enemy->position.x = dis(gen) * (game.getWindowWidth() - enemy->width);

    // 垂直位置设在屏幕上方（刚好不可见）
    enemy->position.y = -enemy->height;

    // 添加到活动敌机列表
    enemySC.getEnemies().push_back(enemy);
}