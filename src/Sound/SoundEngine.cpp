#include "SoundEngine.h"

SoundEngine::SoundEngine() {
    // Initialize SDL_mixer with desired audio settings
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // Handle the error
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
    }
}

SoundEngine::~SoundEngine() {
    // Cleanup
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(soundEffect);
    Mix_CloseAudio();
}

void SoundEngine::playSoundEffect(const std::string &soundFilePath) {
    soundEffect = Mix_LoadWAV(soundFilePath.c_str());
    if (soundEffect == nullptr) {
        SDL_Log("Failed to load sound effect! SDL_mixer Error: %s", Mix_GetError());
        return;
    }
    Mix_VolumeChunk(soundEffect, effectVolume);
    Mix_PlayChannel(-1, soundEffect, 0);  // Play on the first free unreserved channel
}

void SoundEngine::startBackgroundMusic(const std::string &musicFilePath) {
    backgroundMusic = Mix_LoadMUS(musicFilePath.c_str());
    if (backgroundMusic == nullptr) {
        SDL_Log("Failed to load background music! SDL_mixer Error: %s", Mix_GetError());
        return;
    }
    Mix_VolumeMusic(musicVolume);
    Mix_PlayMusic(backgroundMusic, -1);  // Loop indefinitely
}

void SoundEngine::stopBackgroundMusic() {
    Mix_HaltMusic();
}

void SoundEngine::continueBackgroundMusic() {
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(backgroundMusic, -1);
    }
}

void SoundEngine::increaseMusicVolume() {
    musicVolume += 10;  // Increase volume by 10 (for example)
    if (musicVolume > MIX_MAX_VOLUME) musicVolume = MIX_MAX_VOLUME;
    Mix_VolumeMusic(musicVolume);
}

void SoundEngine::decreaseMusicVolume() {
    musicVolume -= 10;  // Decrease volume by 10
    if (musicVolume < 0) musicVolume = 0;
    Mix_VolumeMusic(musicVolume);
}

void SoundEngine::increaseEffectVolume() {
    effectVolume += 10;  // Increase volume by 10 (for example)
    if (effectVolume > MIX_MAX_VOLUME) effectVolume = MIX_MAX_VOLUME;
}

void SoundEngine::decreaseEffectVolume() {
    effectVolume -= 10;  // Decrease volume by 10
    if (effectVolume < 0) effectVolume = 0;
}
