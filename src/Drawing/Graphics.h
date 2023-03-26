#ifndef BOSCONIAN_GRAPHICS_H
#define BOSCONIAN_GRAPHICS_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../Utilities/Vector2D.h"
#include "../Renderer/Renderer.h"
#include "Image.h"

namespace Drawing {

    class Graphics {
    private:
        SDL_Renderer* g_renderer;
    public:
        Graphics(Renderer::RendererSDL* renderer);

        void line(SDL_Color color, Utils::Vector2D from, Utils::Vector2D to);
        void rectangle(SDL_Color color, SDL_Rect rect);
        void fillRectangle2(SDL_Color color, SDL_Rect rect);
        void fillRectangle(SDL_Color color, SDL_FRect rect);

        void string(std::string text, TTF_Font* font, SDL_Color color, Utils::Vector2D pos);
    };

} // Drawing

#endif //BOSCONIAN_GRAPHICS_H
