#ifndef BOSCONIAN_RENDERENGINE_H
#define BOSCONIAN_RENDERENGINE_H

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "HUD.h"
#include "../Model/Camera.h"
#include "../Model/Entity/Player.h"
#include "../Menu/MainMenu.h"

// Enum to represent different fonts.
enum : uint32_t {
    FONT_JOYSTIX_38PX = 0,  // Larger Joystix font
    FONT_JOYSTIX_16PX,      // Smaller Joystix font

    FONT_MAX                // Maximum number of font options
};

class RenderEngine {
public:
    RenderEngine(int windowWidth, int windowHeight);
    ~RenderEngine();

    void Render(const GameSession& session, const Camera& camera); // We'll add more parameters as necessary.
    void Render(const MainMenu& mainMenu);
    void RenderObject(const Entity &object, const GameMap &gameMap);

    void beginScene() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void endScene() {
        SDL_RenderPresent(renderer);
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<TTF_Font*> fonts; // Vector to store TTF_Font pointers

    int width, height;

    /**
     * Add a font from memory to the renderer.
     * \param mem Pointer to the memory containing the font data.
     * \param size Size of the font data in bytes.
     * \param fontIndex Index of the font to add.
     * \param fontPT Point size of the font.
     */
    void addFont(const void* mem, int size, int fontIndex, int fontPT);

    void InitializeSDL();
    void CleanupSDL();

};

#endif //BOSCONIAN_RENDERENGINE_H
