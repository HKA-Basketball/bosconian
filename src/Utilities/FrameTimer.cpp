#include "FrameTimer.h"

FrameTimer::FrameTimer() : FrameTimer(60) {}

FrameTimer::FrameTimer(Uint16 maxFps) : lastFrameTime(SDL_GetTicks64()), deltaTime(0.0f) {
    delayTime = maxFps > 0 ? 1000.f/static_cast<float>(maxFps) : 0;
}

void FrameTimer::startFrame() {
    Uint64 frameStart = SDL_GetTicks64();
    deltaTime = static_cast<float>(frameStart - lastFrameTime) / 1000.0f;
    lastFrameTime = frameStart;
}

float FrameTimer::getDeltaTime() const {
    return deltaTime;
}

void FrameTimer::delayFrame() const {
    Uint64 frameTime = SDL_GetTicks64() - lastFrameTime;
    if (frameTime < delayTime) {
        SDL_Delay(static_cast<Uint32>(delayTime - frameTime));
    }
}
