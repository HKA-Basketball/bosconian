#ifndef BOSCONIAN_FRAMETIMER_H
#define BOSCONIAN_FRAMETIMER_H

#include <SDL.h>

class FrameTimer {
public:
    FrameTimer();
    explicit FrameTimer(Uint16 fps);

    void startFrame();
    float getDeltaTime() const;
    void delayFrame() const;

private:
    float delayTime;
    Uint64 lastFrameTime;
    float deltaTime;
};

#endif //BOSCONIAN_FRAMETIMER_H
