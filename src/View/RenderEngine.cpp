#include "RenderEngine.h"
#include <cstdio>

#include "../../Resources/fonts.h"

RenderEngine::RenderEngine(int windowWidth, int windowHeight)
        : width(windowWidth), height(windowHeight) {
    InitializeSDL();
}

RenderEngine::~RenderEngine() {
    CleanupSDL();
}

void RenderEngine::addFont(const void *mem, int size, int fontIndex, int fontPT) {
    SDL_RWops* pFontMem = SDL_RWFromConstMem(mem, size);

    if(!pFontMem) {
        fprintf(stderr, "SDL_ttf could not initialize font memory! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }

    fonts[fontIndex] = TTF_OpenFontRW(pFontMem, 1, fontPT);

    if (!fonts[fontIndex]) {
        fprintf(stderr, "SDL_ttf could not load font index (%d)! TTF_Error: %s\n", fontIndex, TTF_GetError());
        exit(1);
    }

}

void RenderEngine::InitializeSDL() {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); // needed?

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle the error, for now just print to stderr
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Top-Down Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_SHOWN);

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

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF could not be initialized! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }

    fonts.resize(FONT_MAX);

    addFont(joystix_ttf, sizeof(joystix_ttf), FONT_JOYSTIX_38PX, 38);
    addFont(joystix_ttf, sizeof(joystix_ttf), FONT_JOYSTIX_16PX, 16);

}

void RenderEngine::CleanupSDL() {
    // Clean up fonts
    for (TTF_Font* font : fonts) {
        TTF_CloseFont(font);
    }
    fonts.clear();
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RenderEngine::RenderObject(const Entity& object, const GameMap& gameMap) {
    int worldWidth = gameMap.getWidth();
    int worldHeight = gameMap.getHeight();
    // ... rest of the rendering code ...
}

void RenderEngine::Render(const GameSession& session, const Camera& camera) {
    // Center the camera on the player.
    //camera.centerOn(session.getPlayer());

    // Render game objects.
    /*for (const auto& obj : session.getObjects()) {
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
    }*/

    // Render player.
    //RenderPlayer(session.getPlayer());
}

void RenderEngine::Render(const MainMenu &mainMenu) {
    // Get the menu options and selected index from the mainMenu object
    const auto& options = mainMenu.getOptions();
    size_t selectedIndex = mainMenu.getSelectedIndex();

    // Define colors for normal and selected menu options
    SDL_Color normalColor = {255, 255, 255, 255}; // White color for normal options
    SDL_Color selectedColor = {255, 0, 0, 255};   // Red color for selected option

    // Calculate total menu height to centralize vertically
    int totalMenuHeight = 0;
    for (const auto& option : options) {
        int textWidth, textHeight;
        TTF_SizeText(fonts[FONT_JOYSTIX_38PX], option.c_str(), &textWidth, &textHeight);
        totalMenuHeight += textHeight + 10; // Adding 10 as a padding between menu items
    }

    int y = (height - totalMenuHeight) / 2;

    // Render each menu option
    for (size_t i = 0; i < options.size(); ++i) {
        SDL_Color color = (i == selectedIndex) ? selectedColor : normalColor;
        int textWidth, textHeight;
        TTF_SizeText(fonts[FONT_JOYSTIX_38PX], options[i].c_str(), &textWidth, &textHeight);

        int x = (width - textWidth) / 2; // Centralize horizontally
        // Create a surface from the text
        SDL_Surface* surface = TTF_RenderText_Blended(fonts[FONT_JOYSTIX_38PX], options[i].c_str(), color);

        // Create a texture from the surface
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Free the surface
        SDL_FreeSurface(surface);

        // Define the destination rectangle for the texture
        SDL_Rect dstRect = {x, y, textWidth, textHeight};

        // Copy the texture to the rendering target
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        // Destroy the texture
        SDL_DestroyTexture(texture);

        y += textHeight + 10; // Move y down for next item with padding
    }
}
