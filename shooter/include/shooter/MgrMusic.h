#ifndef MUSIC_MGR_H
#define MUSIC_MGR_H

#include <SDL_mixer.h>

#include <map>
#include <string>

class MusicMgr {
public:
    static MusicMgr &getInstance() {
        static MusicMgr instance;
        return instance;
    }
    ~MusicMgr() = default;

    void init();
    void clean();

    void soundBgm() {
        Mix_PlayMusic(bgm, -1);
    }

    void soundHit() {
        Mix_PlayChannel(-1, sounds["hit"], 0);
    }

    void soundShootPlayer() {
        Mix_PlayChannel(-1, sounds["player_shoot"], 0);
    }

    void soundShootEnemy() {
        Mix_PlayChannel(-1, sounds["enemy_shoot"], 0);
    }

    void soundExplodePlayer() {
        Mix_PlayChannel(-1, sounds["player_explode"], 0);
    }

    void soundExplodeEnemy() {
        Mix_PlayChannel(-1, sounds["enemy_explode"], 0);
    }

    void soundGetItem() {
        Mix_PlayChannel(-1, sounds["get_item"], 0);
    }

private:
    MusicMgr() = default;

    // 删除拷贝与赋值构造函数
    MusicMgr(const MusicMgr &) = delete;
    MusicMgr &operator=(const MusicMgr &) = delete;

    // 背景音乐
    Mix_Music *bgm;
    // 存储音效
    std::map<std::string, Mix_Chunk *> sounds;
};

#endif // MUSIC_MGR_H