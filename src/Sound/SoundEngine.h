#ifndef BOSCONIAN_SOUNDENGINE_H
#define BOSCONIAN_SOUNDENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class SoundEngine {
private:
    Mix_Music* backgroundMusic{nullptr};     // Pointer to background music track
    Mix_Chunk* soundEffect{nullptr};         // Pointer to a sound effect
    int volume{5};                           // Represents the volume level (range [0, MIX_MAX_VOLUME])

public:
    SoundEngine();
    ~SoundEngine();

    // Play a sound effect once
    void playSoundEffect(const std::string& soundFilePath);

    // Start background music in a loop
    void startBackgroundMusic(const std::string& musicFilePath);

    // Stop the background music
    void stopBackgroundMusic();

    // Continue the background music
    void continueBackgroundMusic();

    // Increase the volume
    void increaseVolume();

    // Decrease the volume
    void decreaseVolume();
};

#endif //BOSCONIAN_SOUNDENGINE_H
