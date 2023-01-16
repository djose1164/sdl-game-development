#include "SoundManager.h"

#include <SDL2/SDL.h>

#define checkError(ptr)                                          \
    do                                                           \
    {                                                            \
        if (!(ptr))                                              \
        {                                                        \
            SDL_Log("Could not load media: %s", Mix_GetError()); \
            return false;                                        \
        }                                                        \
    } while (0)

#define file_loaded(f) SDL_LOG("[%s] added to sound manager.", (f))

SoundManager *SoundManager::instance_{nullptr};

SoundManager::SoundManager()
{
    Mix_OpenAudio(22'050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

SoundManager *SoundManager::instance()
{
    if (!instance_)
        instance_ = new SoundManager;

    return instance_;
}

bool SoundManager::load(std::string_view filename, std::string_view id, SoundType type)
{
    switch (type)
    {
    case SoundType::SOUND_MUSIC:
    {
        auto music{Mix_LoadMUS(filename.data())};

        checkError(music);

        music_[id] = music;
        return true;
    }
    case SoundType::SOUND_SFX:
    {
        auto chunk{Mix_LoadWAV(filename.data())};

        checkError(chunk);

        sfxs_[id] = chunk;
        return true;
    }
    }
    return false;
}

void SoundManager::playSound(std::string_view id, int loop)
{
    Mix_PlayChannel(-1, sfxs_[id], loop);
}

void SoundManager::playMusic(std::string_view id, int loop)
{
    const auto res{Mix_PlayMusic(music_[id], loop)};
    if (res == -1)
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Could not play the music: %s", Mix_GetError());
}
