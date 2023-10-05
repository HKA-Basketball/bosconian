#ifndef BOSCONIAN_SOUNDENGINE_H
#define BOSCONIAN_SOUNDENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

/**
 * @class SoundEngine
 * @brief A class responsible for playing sounds and music using SDL_mixer.
 */
class SoundEngine {
private:
    Mix_Music* backgroundMusic{nullptr};     ///< Pointer to background music track.
    Mix_Chunk* soundEffect{nullptr};         ///< Pointer to a sound effect.
    int musicVolume{2};                      ///< Volume level for music (range [0, MIX_MAX_VOLUME]).
    int effectVolume{3};                     ///< Volume level for sound effects (range [0, MIX_MAX_VOLUME]).

public:
    /**
     * @brief Default constructor.
     * Initializes SDL_mixer with the desired audio settings.
     */
    SoundEngine();

    /**
     * @brief Destructor.
     * Cleans up and releases the resources.
     */
    ~SoundEngine();

    /**
     * @brief Play a specific sound effect once.
     * @param soundFilePath Path to the sound effect file.
     */
    void playSoundEffect(const std::string& soundFilePath);

    /**
     * @brief Start playing background music in a loop.
     * @param musicFilePath Path to the music file.
     */
    void startBackgroundMusic(const std::string& musicFilePath);

    /**
     * @brief Stop the currently playing background music.
     */
    void stopBackgroundMusic();

    /**
     * @brief Continue playing the background music if it's paused or stopped.
     */
    void continueBackgroundMusic();

    /**
     * @brief Increase the volume of the background music.
     */
    void increaseMusicVolume();

    /**
     * @brief Decrease the volume of the background music.
     */
    void decreaseMusicVolume();

    /**
     * @brief Increase the volume of sound effects.
     */
    void increaseEffectVolume();

    /**
     * @brief Decrease the volume of sound effects.
     */
    void decreaseEffectVolume();
};


#endif //BOSCONIAN_SOUNDENGINE_H
