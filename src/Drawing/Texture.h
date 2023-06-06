#ifndef BOSCONIAN_TEXTURE_H
#define BOSCONIAN_TEXTURE_H

#include "../../includes.h"
#include "Graphics.h"
#include "../Utilities/GlobalVars.h"

namespace Drawing {

    class Texture {
    private:
        Drawing::Graphics* g_drawing;

    public:
        std::string name;

        SDL_Texture* imgTex;
        bool clipped;
        SDL_Rect renderRect;
        SDL_Rect clipRect;
        float angle;

        Texture(std::string filename, float deg = 0.f, bool clipped = false, std::string spritesheet = "");

        bool changeTexture(std::string filename, bool clipped = false, std::string spritesheet = "");

        void setSize(Utils::Vector2D newSize);
        Utils::Vector2D getSize();

        void setPos(Utils::Vector2D newPos);
        Utils::Vector2D getPos();

        void setAngel(float newAngel);
        float getAngel();

        void draw();
    };

} // Drawing

#endif //BOSCONIAN_TEXTURE_H
