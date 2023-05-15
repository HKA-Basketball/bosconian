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

    void Graphics::string(std::string text, TTF_Font* font, SDL_Color color, Utils::Vector2D pos)
    {
        SDL_Surface* surface;
        SDL_Texture* texture;

        // Create an SDL_Surface with the text to render
        surface = TTF_RenderText_Blended(font, text.c_str(), color);

        // Create an SDL_Texture from the SDL_Surface
        texture = SDL_CreateTextureFromSurface(g_renderer, surface);

        SDL_Rect destR = { (int)pos.x, (int)pos.y, surface->w, surface->h };
        //TTF_SizeText(font, text.c_str(), &destR.w, &destR.h);

        SDL_FreeSurface(surface);
        SDL_RenderCopy(g_renderer, texture, NULL, &destR);
        SDL_DestroyTexture(texture);
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
        if(tex == NULL) {
            printf("Image Load Error: Path(%s) - Error(%s)\n", filename.c_str(), IMG_GetError());
            printf("Create Texture Error: %s\n", SDL_GetError());
            return tex;
        }

        return tex;
    }
} // Drawing