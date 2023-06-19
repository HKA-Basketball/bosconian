#include "SoundManager.h"

namespace Sound {
    SoundManager* g_sound;

    SoundManager::SoundManager() {
        if (!initSDL_OA())
            throw std::runtime_error("Failed to init SDL_OpenAudio");

        m_sound.resize(SOUND_MAX);

        // credits: Music by Marllon Silva (xDeviruchi)
        addSound("./loop.wav", SOUND_BG);
        // credits: Sound by Muncheybobo @ opengameart.org
        addSound("./shoot.wav", SOUND_SHOOT);
        // credits: mixkit.co/free-sound-effects/arcade/
        addSound("./game_over.wav", SOUND_GAME_OVER);
        addSound("./explode.wav", SOUND_EXPLODE);


        LOG(std::string("SoundManager Successfully Loaded"));
    }

    bool SoundManager::initSDL_OA() {
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            LOG(std::string("Error intializing SDL2_mixer:") + SDL_GetError());
            return 0;
        }

        return 1;
    }

    bool SoundManager::addSound(const void *mem, int size, int soundIndex) {
        SDL_RWops* pWavMem = SDL_RWFromConstMem(mem, size);

        if(!pWavMem)
        {
            LOG(std::string("Error loading WAV Data:") + SDL_GetError());
            return 0;
        }

        Mix_Chunk* waves = Mix_LoadWAV_RW(pWavMem, 1);

        if(!waves)
        {
            LOG(std::string("Error loading waves Data:") + SDL_GetError());
            return 0;
        }

        m_sound[soundIndex] = waves;
        LOG(std::string("Sound Added"));

        return 1;
    }

    bool SoundManager::addSound(const char *file, int soundIndex) {
        Mix_Chunk* waves = Mix_LoadWAV(file);

        if(!waves)
        {
            LOG(std::string("Error loading waves Data:") + SDL_GetError());
            return 0;
        }

        m_sound[soundIndex] = waves;
        LOG(std::string("Sound Added ") + file);

        return 1;
    }

    void SoundManager::playSound(int soundIndex, int volume, int loops) {
        if (Mix_PlayChannel(soundIndex, m_sound[soundIndex], loops) == -1)
        {
            LOG(std::string("Error Waves sound could not be played!:") + SDL_GetError());
            //Mix_FreeChunk(m_sound[soundIndex]);
            return;
        }

        Mix_Volume(soundIndex, volume);
    }

    void SoundManager::setVolume(int soundIndex, int volume) {
        Mix_Volume(soundIndex, volume);
    }

    void SoundManager::stopSound(int soundIndex) {
        Mix_Paused(soundIndex);
    }

    void SoundManager::stopAllSound() {
        Mix_Paused(-1);
    }

    void SoundManager::resumeSound(int soundIndex) {
        Mix_Resume(soundIndex);
    }

    void SoundManager::freeSound(int soundIndex) {
        Mix_FreeChunk(m_sound[soundIndex]);
    }

    void SoundManager::freeAllSounds() {
        for (auto wave : m_sound) {
            Mix_FreeChunk(wave);
        }
    }


} // Sound