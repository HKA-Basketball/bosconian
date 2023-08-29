#include "Graphics.h"

namespace Drawing {
    Graphics* g_drawing;

    Graphics::Graphics() {
        g_renderer = Renderer::g_renderer->renderer;
        if (!g_renderer) {
            LOG("Error: Renderer is nullptr");
            throw std::runtime_error("Failed to init Graphics");
        }

        LOG(std::string("Graphics Successfully created"));
    }

    void Graphics::line(SDL_Color color, Utils::Vector2D from, Utils::Vector2D to) {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLineF(g_renderer, from.x, from.y, to.x, to.y);
    }

    void Graphics::rectangle(SDL_Color color, SDL_Rect rect)
    {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(g_renderer, &rect);
    }

    void Graphics::rotatedRectangle(const SDL_Color color, const SDL_Rotated_Rect rotatedRect) {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        sdl_rotated_rect(g_renderer, rotatedRect);
    }

    void Graphics::fillRectangle(SDL_Color color, SDL_Rect rect)
    {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);
    }

    void Graphics::fillRectangle(SDL_Color color, SDL_FRect rect)
    {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRectF(g_renderer, &rect);
    }

    void Graphics::fillRectangleOutline(SDL_Color color, SDL_Rect rect)
    {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);

        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, color.a);
        SDL_RenderDrawRect(g_renderer, &rect);
    }

    void Graphics::fillRectangleOutline(SDL_Color color, SDL_FRect rect)
    {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRectF(g_renderer, &rect);

        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, color.a);
        SDL_RenderDrawRectF(g_renderer, &rect);
    }

    void Graphics::texture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx(g_renderer, tex, clip, rend, angle, NULL, flip);
    }

    void Graphics::string(std::string text, TTF_Font* font, SDL_Color color, Utils::Vector2D pos, int alignment)
    {
        SDL_Texture* texture = getText(text, font, color).get();

        int textWidth, textHeight;
        TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

        SDL_Rect destRect;
        destRect.w = textWidth;
        destRect.h = textHeight;

        switch (alignment) {
            case Left:
                destRect.x = static_cast<int>(pos.x);
                destRect.y = static_cast<int>(pos.y);
                break;
            case Right:
                destRect.x = static_cast<int>(pos.x - textWidth);
                destRect.y = static_cast<int>(pos.y);
                break;
            case Center:
                destRect.x = static_cast<int>(pos.x - (textWidth / 2));
                destRect.y = static_cast<int>(pos.y - (textHeight / 2));
                break;
        }

        SDL_RenderCopy(g_renderer, texture, NULL, &destRect);
    }

    SDL_Texture* Graphics::getTexture(std::string filename) {
        std::string fullPath = SDL_GetBasePath();
        fullPath.append("images/" + filename);

        if(textures[fullPath] == nullptr)
            textures[fullPath] = loadTexture(fullPath);

        return textures[fullPath];
    }

    SDL_Texture* Graphics::loadTexture(std::string filename) {
        SDL_Texture* tex = IMG_LoadTexture(g_renderer, filename.c_str());
        if(!tex) {
            LOG(std::string("Texture Load Error: Path(") + filename.c_str() + ")" + " - Error(" + IMG_GetError() + ")");
            LOG(std::string("Create Texture Error: ") + SDL_GetError());
            return tex;
        }

        return tex;
    }

    std::shared_ptr<SDL_Texture> Graphics::getText(std::string text, TTF_Font* font, SDL_Color color) {
        std::string key = text + (char)color.r + (char)color.b + (char)color.g;

        auto cacheIter = textCache.find(key);
        if (cacheIter == textCache.end()) {
            textCache[key] = { createTextTexture(text, font, color), 1 };

            if (textCache.size() > MAX_CACHE_SIZE) {
                // Remove the last used item from the cache
                std::string& oldestKey = accessQueue.front();
                textCache.erase(oldestKey);
                accessQueue.pop_front();
            }

            accessQueue.push_back(key);
        } else {
            cacheIter->second.accessCount++;

            accessQueue.remove(key);
            accessQueue.push_back(key);
        }

        return textCache[key].texture;
    }

    std::shared_ptr<SDL_Texture> Graphics::createTextTexture(std::string text, TTF_Font* font, SDL_Color color)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        if(!surface) {
            LOG(std::string("Text Render Error: ") + TTF_GetError());
            return NULL;
        }

        std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(g_renderer, surface), SDL_DestroyTexture);
        if(!texture.get()) {
            LOG(std::string("Text Texture Creation Error: ") + SDL_GetError());
            return NULL;
        }

        SDL_FreeSurface(surface);

        return texture;
    }

    void Graphics::sdl_rotated_rect(SDL_Renderer* r, const SDL_Rotated_Rect rotatedRect) {
        // Convert the angle from degrees to radians
        double angleRadians = rotatedRect.angle * (M_PI / 180.0);

        // Calculate the half-width and half-height for rotation
        double halfWidth = rotatedRect.w / 2.0;
        double halfHeight = rotatedRect.h / 2.0;

        // Adjust position to center the rectangle
        const int x0 = rotatedRect.x + halfWidth;
        const int y0 = rotatedRect.y + halfHeight;

        // Calculate the four corner points of the rotated rectangle
        double x1 = x0 + halfWidth * cos(angleRadians) - halfHeight * sin(angleRadians);
        double y1 = y0 + halfWidth * sin(angleRadians) + halfHeight * cos(angleRadians);
        double x2 = x0 - halfWidth * cos(angleRadians) - halfHeight * sin(angleRadians);
        double y2 = y0 - halfWidth * sin(angleRadians) + halfHeight * cos(angleRadians);
        double x3 = 2 * x0 - x1;
        double y3 = 2 * y0 - y1;
        double x4 = 2 * x0 - x2;
        double y4 = 2 * y0 - y2;

        // Draw lines between the corner points to form the rotated rectangle
        SDL_RenderDrawLine(r, static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
        SDL_RenderDrawLine(r, static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3));
        SDL_RenderDrawLine(r, static_cast<int>(x3), static_cast<int>(y3), static_cast<int>(x4), static_cast<int>(y4));
        SDL_RenderDrawLine(r, static_cast<int>(x4), static_cast<int>(y4), static_cast<int>(x1), static_cast<int>(y1));
    }

} // Drawing