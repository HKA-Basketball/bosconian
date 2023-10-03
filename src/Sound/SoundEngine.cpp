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
    Mix_VolumeChunk(soundEffect, volume);
    Mix_PlayChannel(-1, soundEffect, 0);  // Play on the first free unreserved channel
}

void SoundEngine::startBackgroundMusic(const std::string &musicFilePath) {
    backgroundMusic = Mix_LoadMUS(musicFilePath.c_str());
    if (backgroundMusic == nullptr) {
        SDL_Log("Failed to load background music! SDL_mixer Error: %s", Mix_GetError());
        return;
    }
    Mix_VolumeMusic(volume);
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

void SoundEngine::increaseVolume() {
    volume += 10;  // Increase volume by 10 (for example)
    if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    Mix_VolumeMusic(volume);
}

void SoundEngine::decreaseVolume() {
    volume -= 10;  // Decrease volume by 10
    if (volume < 0) volume = 0;
    Mix_VolumeMusic(volume);
}
