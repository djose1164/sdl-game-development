#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string_view>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>

enum class SoundType
{
    SOUND_MUSIC,
    SOUND_SFX
};

class SoundManager
{
public:
    static SoundManager *instance();

    bool load(std::string_view filename, std::string_view id, SoundType type);

    void playSound(std::string_view id, int loop);
    void playMusic(std::string_view id, int loop);

private:
    SoundManager();
    ~SoundManager();

    SoundManager(const SoundManager &other);
    SoundManager &operator=(const SoundManager &other);

    static SoundManager *instance_;

    std::unordered_map<std::string_view, Mix_Chunk *> sfxs_;
    std::unordered_map<std::string_view, Mix_Music *> music_;
};

using TheSoundManager = SoundManager;

#endif // SOUND_MANAGER_H
