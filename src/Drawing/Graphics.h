#ifndef BOSCONIAN_GRAPHICS_H
#define BOSCONIAN_GRAPHICS_H

#include <map>
#include "../../includes.h"
#include "../Renderer/Renderer.h"

namespace Drawing {

    class Graphics {
    private:
        SDL_Renderer* g_renderer;
        //Cache for all loaded images
        std::map<std::string, SDL_Texture*> textures;

    public:
        Graphics(Renderer::RendererSDL* renderer);

        void line(SDL_Color color, Utils::Vector2D from, Utils::Vector2D to);
        void rectangle(SDL_Color color, SDL_Rect rect);
        void fillRectangle2(SDL_Color color, SDL_Rect rect);
        void fillRectangle(SDL_Color color, SDL_FRect rect);
        void fillRectangleOutline(SDL_Color color, SDL_Rect rect);
        void texture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void string(std::string text, TTF_Font* font, SDL_Color color, Utils::Vector2D pos);

        // TODO: May add AssetManager?
        SDL_Texture* getTexture(std::string filename);
        SDL_Texture* loadTexture(std::string filename);
    };

} // Drawing

#endif //BOSCONIAN_GRAPHICS_H
