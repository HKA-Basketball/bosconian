#include "RenderEngine.h"
#include <stdio.h>

RenderEngine::RenderEngine(int windowWidth, int windowHeight)
        : width(windowWidth), height(windowHeight) {
    InitializeSDL();
}

RenderEngine::~RenderEngine() {
    CleanupSDL();
}

void RenderEngine::InitializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle the error, for now just print to stderr
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Top-Down Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        exit(1);
    }
}

void RenderEngine::CleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RenderEngine::RenderObject(const Entity& object, const GameMap& gameMap) {
    int worldWidth = gameMap.getWidth();
    int worldHeight = gameMap.getHeight();
    // ... rest of the rendering code ...
}


void RenderEngine::Render(const Player& player, const HUD& hud) {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // For now, clear to black.
    SDL_RenderClear(renderer);

    // Render game objects. Order matters.
    player.Render(renderer);  // For this to work, you need a Render() method in Player class.
    hud.Render(renderer);  // Likewise, Render() is needed in HUD class.

    // Update the screen
    SDL_RenderPresent(renderer);
}

void RenderEngine::Render(const GameSession& session, const Camera& camera) {
    // Center the camera on the player.
    camera.centerOn(session.getPlayer());

    // Render game objects.
    for (const auto& obj : session.getObjects()) {
        if (camera.isInView(obj)) {
            RenderObject(obj);
        }

        // Handle world wrapping.
        // This is a simple example, but you'd probably need to expand upon it.
        if (obj.getX() - obj.getWidth() < 0) {
            Entity wrappedObj = obj;
            wrappedObj.setX(session.getGameMap().getWidth() + obj.getX());
            RenderObject(wrappedObj);
        }
        // Similarly for other directions (right, top, bottom).
    }

    // Render player.
    RenderPlayer(session.getPlayer());
}
