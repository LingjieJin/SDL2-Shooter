#include "shooter/MgrMusic.h"

#include <SDL.h>


void MusicMgr::init() {
    // 初始化SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                     Mix_GetError());
    }
    //
    // 打开音频设备
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "SDL_mixer could not open audio! SDL_mixer Error: %s\n",
                     Mix_GetError());
    }

    // 设置音效channel数量
    Mix_AllocateChannels(32);

    // 设置音乐和音效音量
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_Volume(-1, MIX_MAX_VOLUME / 8);

    //
    // 读取背景音乐
    bgm = Mix_LoadMUS("../assets/music/03_Racing_Through_Asteroids_Loop.ogg");
    if (bgm == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s",
                     Mix_GetError());
    }

    // 读取音效资源
    sounds["player_shoot"] = Mix_LoadWAV("../assets/sound/laser_shoot4.wav");
    sounds["enemy_shoot"] = Mix_LoadWAV("../assets/sound/xs_laser.wav");
    sounds["player_explode"] = Mix_LoadWAV("../assets/sound/explosion1.wav");
    sounds["enemy_explode"] = Mix_LoadWAV("../assets/sound/explosion3.wav");
    sounds["hit"] = Mix_LoadWAV("../assets/sound/eff11.wav");
    sounds["get_item"] = Mix_LoadWAV("../assets/sound/eff5.wav");
}

void MusicMgr::clean() {
    // 清理容器
    for (auto sound : sounds) {
        if (sound.second != nullptr) {
            Mix_FreeChunk(sound.second);
        }
    }
    sounds.clear();

    // 清理音乐资源
    if (bgm != nullptr) {
        Mix_HaltMusic();
        Mix_FreeMusic(bgm);
    }

    // 清理SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();
}