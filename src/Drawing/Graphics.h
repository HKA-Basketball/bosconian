#ifndef BOSCONIAN_GRAPHICS_H
#define BOSCONIAN_GRAPHICS_H

#include <map>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <memory>
#include "../../includes.h"
#include "../Renderer/Renderer.h"

namespace Drawing {

    enum : uint32_t {
        Left = 0,
        Right,
        Center
    };

    class Graphics {
    private:
        const int MAX_CACHE_SIZE = 100;

        struct TextCacheItem {
            std::shared_ptr<SDL_Texture> texture;
            int accessCount;
        };

        SDL_Renderer* g_renderer;
        //Caching
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TextCacheItem> textCache;
        std::list<std::string> accessQueue;

    public:
        Graphics(Renderer::RendererSDL* renderer);

        void line(SDL_Color color, Utils::Vector2D from, Utils::Vector2D to);
        void rectangle(SDL_Color color, SDL_Rect rect);
        void fillRectangle2(SDL_Color color, SDL_Rect rect);
        void fillRectangle(SDL_Color color, SDL_FRect rect);
        void fillRectangleOutline(SDL_Color color, SDL_Rect rect);
        void texture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void string(std::string text, TTF_Font* font, SDL_Color color, Utils::Vector2D pos, int alignment = Left);

        // TODO: May add AssetManager?
        SDL_Texture* getTexture(std::string filename);
        SDL_Texture* loadTexture(std::string filename);

        std::shared_ptr<SDL_Texture> getText(std::string text, TTF_Font *font, SDL_Color color);
        std::shared_ptr<SDL_Texture> creatTextTexture(std::string text, TTF_Font* font, SDL_Color color);
    };

} // Drawing

#endif //BOSCONIAN_GRAPHICS_H
