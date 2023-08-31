#ifndef BOSCONIAN_RENDERENGINE_H
#define BOSCONIAN_RENDERENGINE_H

#pragma once

#include <SDL.h>
#include "../Model/Entity/Player.h"
#include "HUD.h"

class RenderEngine {
public:
    RenderEngine(int windowWidth, int windowHeight);
    ~RenderEngine();

    void Render(const Player& player, const HUD& hud); // We'll add more parameters as necessary.

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;

    void InitializeSDL();
    void CleanupSDL();
};

#endif //BOSCONIAN_RENDERENGINE_H
