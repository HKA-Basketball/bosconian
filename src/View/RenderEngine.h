#ifndef BOSCONIAN_RENDERENGINE_H
#define BOSCONIAN_RENDERENGINE_H

#pragma once

#include <array>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Graphic/Sprite.h"
#include "../Graphic/Fonts.h"

#include "../Utilities/Config.h"
#include "../Utilities/Vector2D.h"
#include "../Utilities/Degree.h"
#include "../Model/Menus/MenuItem.h"

class RenderEngine {
private:
    static RenderEngine* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* spritesheet;
    std::array<TTF_Font*, Font::Type::MAX> fonts;

    int width{Config::windowWidth};
    int height{Config::windowHeight};

    void InitializeSDL();
    void CleanupSDL();

    void loadSpritesheet();
    void unloadSpritesheet();

    void loadFonts();
    void unloadFonts();

    // Private constructor and destructor to prevent instantiation
    RenderEngine() {
        InitializeSDL();
        loadSpritesheet();
        loadFonts();
    }
    ~RenderEngine() {
        unloadSpritesheet();
        unloadFonts();
        CleanupSDL();
    }

    // Private copy constructor and assignment operator to prevent copying
    RenderEngine(const RenderEngine&) = delete;
    RenderEngine& operator=(const RenderEngine&) = delete;

public:
    static RenderEngine* Instance() {
        if (!instance) {
            instance = new RenderEngine();
            return instance;
        }
        return instance;
    }

    void beginScene() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void endScene() {
        SDL_RenderPresent(renderer);
    }

    void renderLine(const Vector2D &start, const Vector2D &end, const SDL_Color &color);

    void renderCone(const Vector2D &start, const Vector2D &apex, const Vector2D &end, const SDL_Color &color);

    void renderRectangle(const Vector2D &position, const Vector2D &size, const SDL_Color &color, bool filled = false);

    void renderRotatedRectangle(const Vector2D &position, const Vector2D &size, const Degree &angle, const SDL_Color& color);

    void renderSprite(Sprite& sprite, float angle = 0.0, bool centered = false, SDL_FPoint* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void renderText(const std::string& text, const Vector2D& position, const SDL_Color& color, const uint32_t& fontIndex, bool centered = false) const;

    void renderMenuItem(const MenuItem& menuItem, const SDL_Color& color, const uint32_t& fontIndex) const;

    SDL_Renderer* getRenderer() const {
        return renderer;
    }

    TTF_Font* getFont(Font::Type fontType) {
        return fonts.at(fontType);
    }
};

#endif //BOSCONIAN_RENDERENGINE_H