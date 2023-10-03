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
#include "../Model/Menus/Items/MenuItem.h"
#include "../Model/Menus/Items/SwitchItem.h"
#include "../Graphic/TextAlign.h"

class RenderEngine {
private:
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

    // Private copy constructor and assignment operator to prevent copying
    //RenderEngine(const RenderEngine&) = delete;
    //RenderEngine& operator=(const RenderEngine&) = delete;

public:
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

    void beginScene() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void endScene() {
        SDL_RenderPresent(renderer);
    }

    void renderLine(const Vector2D &start, const Vector2D &end, const SDL_Color &color) const;

    void renderCone(const Vector2D &start, const Vector2D &apex, const Vector2D &end, const SDL_Color &color) const;

    void renderRectangle(const Vector2D &position, const Vector2D &size, const SDL_Color &color, bool filled = false) const;

    void renderRotatedRectangle(const Vector2D &position, const Vector2D &size, const Degree &angle, const SDL_Color& color) const;

    void renderSprite(Sprite& sprite, float angle = 0.0, bool centered = false, SDL_FPoint* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void renderText(const std::string& text, const Vector2D& position, const SDL_Color& color = Config::ColorWhite, const uint32_t& fontIndex = Font::JOYSTIX_38PX, TextAlign align = TextAlign::LEFT) const;

    void renderMenuItem(const MenuItem& menuItem, const SDL_Color& color = Config::ColorWhite, const uint32_t& fontIndex = Font::JOYSTIX_38PX) const;

    void renderSwitchItem(const SwitchItem &switchItem, const SDL_Color &color, const SDL_Color &textColor = Config::ColorWhite,
                          const uint32_t &fontIndex = Font::JOYSTIX_38PX) const;

    SDL_Renderer* getRenderer() const {
        return renderer;
    }

    TTF_Font* getFont(Font::Type fontType) {
        return fonts.at(fontType);
    }
};

#endif //BOSCONIAN_RENDERENGINE_H
