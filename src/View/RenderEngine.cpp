#include "RenderEngine.h"
#include "../Utilities/Math.h"

#include <cstdio>


// Initialize the static instance pointer to nullptr
RenderEngine* RenderEngine::instance = nullptr;

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

}

void RenderEngine::loadSpritesheet() {
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("images/spritesheet.png");

    spritesheet = IMG_LoadTexture(renderer, fullPath.c_str());

    if(!spritesheet) {
        fprintf(stderr, "Spritesheet could not load Texture\n");
    }
}

void RenderEngine::unloadSpritesheet() {
    SDL_DestroyTexture(spritesheet);
}

void RenderEngine::loadFonts() {
    fonts[Font::Type::JOYSTIX_128PX] = TTF_OpenFont("fonts/joystix_monospace.otf", 128);
    fonts[Font::Type::JOYSTIX_64PX] = TTF_OpenFont("fonts/joystix_monospace.otf", 64);
    fonts[Font::Type::JOYSTIX_38PX] = TTF_OpenFont("fonts/joystix_monospace.otf", 38);
    fonts[Font::Type::JOYSTIX_24PX] = TTF_OpenFont("fonts/joystix_monospace.otf", 24);
    fonts[Font::Type::JOYSTIX_16PX] = TTF_OpenFont("fonts/joystix_monospace.otf", 16);
    // Load more fonts as needed

    // Check for errors in loading fonts
    for (auto font : fonts) {
        if (!font) {
            // Handle error
        }
    }
}

void RenderEngine::unloadFonts() {
    for (auto font : fonts) {
        TTF_CloseFont(font);
    }
}

void RenderEngine::CleanupSDL() {
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RenderEngine::renderLine(const Vector2D &start, const Vector2D &end, const SDL_Color& color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
}

void RenderEngine::renderCone(const Vector2D &start, const Vector2D &apex, const Vector2D &end, const SDL_Color& color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Define the points of the cone
    SDL_FPoint points[3];
    points[0].x = start.x;
    points[0].y = start.y;
    points[1].x = apex.x;
    points[1].y = apex.y;
    points[2].x = end.x;
    points[2].y = end.y;

    // Draw the lines forming the cone
    SDL_RenderDrawLinesF(renderer, points, 3);
}

void RenderEngine::renderRectangle(const Vector2D &position, const Vector2D &size, const SDL_Color& color, bool filled) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect fRect = {position.x, position.y, size.x, size.y};

    if(filled) {
        SDL_RenderFillRectF(renderer, &fRect);
    } else {
        SDL_RenderDrawRectF(renderer, &fRect);
    }
}

void RenderEngine::renderRotatedRectangle(const Vector2D &position, const Vector2D &size, const Degree &angle, const SDL_Color& color) const {
    float angleRadians = angle.toRadians();
    float halfWidth = size.x / 2.f;
    float halfHeight = size.y / 2.f;

    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);

    SDL_FPoint points[5];

    // Calculate the four corner points of the rotated rectangle
    points[0].x = position.x + halfWidth * cosAngle - halfHeight * sinAngle;
    points[0].y = position.y + halfWidth * sinAngle + halfHeight * cosAngle;

    points[1].x = position.x - halfWidth * cosAngle - halfHeight * sinAngle;
    points[1].y = position.y - halfWidth * sinAngle + halfHeight * cosAngle;

    points[2].x = 2 * position.x - points[0].x;
    points[2].y = 2 * position.y - points[0].y;

    points[3].x = 2 * position.x - points[1].x;
    points[3].y = 2 * position.y - points[1].y;

    points[4] = points[0]; // Close the loop

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLinesF(renderer, points, 5);
}

void RenderEngine::renderSprite(Sprite& sprite, float angle, bool centered, SDL_FPoint* center, SDL_RendererFlip flip) const {
    SDL_Rect srcRect = sprite.getSourceRectangle();
    SDL_FRect destRect = sprite.getDestinationRectangle(centered);
    SDL_RenderCopyExF(renderer, spritesheet, &srcRect, &destRect, angle, center, flip);
}

void RenderEngine::renderText(const std::string& text, const Vector2D& position, const SDL_Color& color, const uint32_t& fontIndex, bool centered) const {
    if (fontIndex >= Font::MAX) return; // Invalid font index
    TTF_Font* font = fonts[fontIndex];

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        // Handle error ...
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        // Handle error ...
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = position.x;
    dstRect.y = position.y;

    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

    if(centered) {
        dstRect.x = dstRect.x - (dstRect.w / 2);
        dstRect.y = dstRect.y - (dstRect.h / 2);
    }

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void RenderEngine::renderMenuItem(const MenuItem& menuItem, const SDL_Color& color, const uint32_t& fontIndex) const {
    SDL_FRect position = menuItem.getBounds();
    renderText(menuItem.getText(), {position.x, position.y}, color, fontIndex, menuItem.isCentered());
}

void RenderEngine::renderSwitchItem(const SwitchItem& switchItem, const SDL_Color& color, const SDL_Color& textColor, const uint32_t& fontIndex) const {
    SDL_FRect textBounds = switchItem.getTextBounds();
    Vector2D textPosition = {textBounds.x + (textBounds.w/2), textBounds.y};
    renderText(switchItem.getText(), textPosition, textColor, fontIndex, true);

    for (int switchIndex = 0; switchIndex < switchItem.getNumSwitches(); ++switchIndex) {
        SDL_FRect switchBound = switchItem.getSwitchBounds().at(switchIndex);
        bool active = Math::getBitAtIndex(switchItem.getState(), switchIndex);

        renderRectangle({switchBound.x, switchBound.y}, {switchBound.w, switchBound.h}, Config::ColorGrey, true);

        switchBound.h /= 2.f;
        switchBound.y += active ? 0 : switchBound.h;
        SDL_Color activeColor = active ? Config::ColorGreen : Config::ColorRed;
        renderRectangle({switchBound.x, switchBound.y}, {switchBound.w, switchBound.h}, activeColor, true);
    }
}