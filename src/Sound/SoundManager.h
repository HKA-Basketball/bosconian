#ifndef BOSCONIAN_SOUNDMANAGER_H
#define BOSCONIAN_SOUNDMANAGER_H

#include "../../includes.h"

namespace Sound {

    /**
     * Enum to represent different sound effects.
     */
    enum : uint32_t
    {
        SOUND_BG = 0,       // Background music
        SOUND_SHOOT,        // Shooting sound
        SOUND_GAME_OVER,    // Game over sound
        SOUND_EXPLODE,      // Explosion sound
        //Space for more sound effects
        SOUND_MAX           // Maximum number of sound effects
    };

    /**
     * \class SoundManager
     * \brief A class responsible for managing sound effects.
     */
    class SoundManager {
    private:
        /**
         * Initialize SDL for audio operations.
         * \return True if initialization was successful, false otherwise.
         */
        bool initSDL_OA();

        /**
         * Add a sound from memory to the sound manager.
         * \param mem Pointer to the memory containing the sound data.
         * \param size Size of the sound data in bytes.
         * \param soundIndex Index of the sound to add.
         * \return True if adding the sound was successful, false otherwise.
         */
        bool addSound(const void *mem, int size, int soundIndex);

        /**
         * Add a sound from a file to the sound manager.
         * \param file Path to the sound file.
         * \param soundIndex Index of the sound to add.
         * \return True if adding the sound was successful, false otherwise.
         */
        bool addSound(const char *file, int soundIndex);

    public:
        std::vector<Mix_Chunk*> m_sound; // Vector to store Mix_Chunk pointers

        /**
         * Constructor for the SoundManager class.
         */
        SoundManager();

        /**
         * Destructor for the SoundManager class.
         * Cleans up allocated Mix_Chunk objects.
         */
        ~SoundManager() {
            // Clean up the Mix chunks
            for (Mix_Chunk* chunk : m_sound) {
                Mix_FreeChunk(chunk);
            }
            m_sound.clear();
        }

        /**
         * Play a sound effect.
         * \param soundIndex Index of the sound effect to play.
         * \param volume Volume level of the sound (0-128).
         * \param loops Number of times to loop the sound (-1 for infinite loop).
         */
        void playSound(int soundIndex, int volume, int loops = -1);

        /**
         * Set the volume of a sound effect.
         * \param soundIndex Index of the sound effect to adjust.
         * \param volume Volume level of the sound (0-128).
         */
        void setVolume(int soundIndex, int volume);

        /**
         * Stop playing a specific sound effect.
         * \param soundIndex Index of the sound effect to stop.
         */
        void stopSound(int soundIndex);

        /**
         * Stop playing all sound effects.
         */
        void stopAllSound();

        /**
         * Resume playing a specific sound effect.
         * \param soundIndex Index of the sound effect to resume.
         */
        void resumeSound(int soundIndex);

        /**
         * Free a specific sound effect.
         * \param soundIndex Index of the sound effect to free.
         */
        void freeSound(int soundIndex);

        /**
         * Free all loaded sound effects.
         */
        void freeAllSounds();

    }; extern SoundManager* g_sound;

} // Sound

#endif //BOSCONIAN_SOUNDMANAGER_H
