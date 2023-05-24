#ifndef BOSCONIAN_SOUNDMANAGER_H
#define BOSCONIAN_SOUNDMANAGER_H

#include "../../includes.h"

namespace Sound {

    enum : uint32_t
    {
        SOUND_BG = 0,
        SOUND_SHOOT,
        //Space for more
        SOUND_MAX
    };

    class SoundManager {
    private:
        bool initSDL_OA();
        bool addSound(const void *mem, int size, int soundIndex);
        bool addSound(const char *file, int soundIndex);

    public:
        std::vector<Mix_Chunk*> m_sound;

        SoundManager();

        ~SoundManager() {
            // Clean up the Mix chunks
            for (Mix_Chunk* chunk : m_sound) {
                Mix_FreeChunk(chunk);
            }
            m_sound.clear();
        }

        void playSound(int soundIndex, int volume, int loops = -1);
        void setVolume(int soundIndex, int volume);
        void stopSound(int soundIndex);
        void stopAllSound();
        void resumeSound(int soundIndex);
        void freeSound(int soundIndex);
        void freeAllSounds();


    };

} // Sound

#endif //BOSCONIAN_SOUNDMANAGER_H
