#include "Graphics.h"

namespace Drawing {
    Graphics::Graphics(Renderer::RendererSDL* renderer) {
        g_renderer = renderer->renderer;
        LOG(std::string("Graphics Successfully created"));
    }

    void Graphics::line(SDL_Color color, Utils::Vector2D from, Utils::Vector2D to) {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(g_renderer, from.x, from.y, to.x, to.y);
    }

    void Graphics::rectangle(SDL_Color color, SDL_Rect rect)
    {
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(g_renderer, &rect);
    }

    void Graphics::fillRectangle2(SDL_Color color, SDL_Rect rect)
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
            textCache[key] = { creatTextTexture(text, font, color), 1 };

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

    std::shared_ptr<SDL_Texture> Graphics::creatTextTexture(std::string text, TTF_Font* font, SDL_Color color)
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
} // Drawing