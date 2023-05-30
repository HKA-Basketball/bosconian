#include "../Utilities/Logging.h"
#include "Texture.h"

namespace Drawing {
    Texture::Texture(Drawing::Graphics* drawing, std::string filename, float deg, bool clipped, std::string spritesheet) {
        this->g_drawing = drawing;
        angle = deg;

        if (!changeTexture(filename, clipped, spritesheet))
            throw std::runtime_error("Failed to Creat texture");
    }

    bool Texture::changeTexture(std::string filename, bool clipped, std::string spritesheet) {
        imgTex = nullptr;
        this->name = filename;

        if (clipped) {
            this->clipped = true;

            int x;
            int y;
            int width;
            int height;
            bool found = false;

            for (const auto& frame : Utils::GlobalVars::frames) {
                if (!frame.filename.compare(filename)) {
                    width = frame.frame.w;
                    height = frame.frame.h;
                    x = frame.frame.x;
                    y = frame.frame.y;
                    found = true;
                }
            }

            if (!found) {
                LOG(std::string("Error frame not found!: ") + SDL_GetError());
                return 0;
            }

            imgTex = g_drawing->getTexture(spritesheet);
            if (!imgTex) {
                LOG(std::string("Error loading Texture: ") + SDL_GetError());
                return 0;
            }

            renderRect.w = width;
            renderRect.h = height;

            //Setting the clipped rectangle to only get the needed texture from the spritesheet
            clipRect.x = x;
            clipRect.y = y;
            clipRect.w = width;
            clipRect.h = height;
        } else {
            imgTex = g_drawing->getTexture(filename);
            if (!imgTex) {
                LOG(std::string("Error loading Texture: ") + SDL_GetError());
                return 0;
            }
            int w, h;
            SDL_QueryTexture(imgTex, NULL, NULL, &w, &h);

            clipped = false;

            renderRect.w = w;
            renderRect.h = h;
        }

        renderRect.x = 0;
        renderRect.y = 0;

        return 1;
    }

    void Texture::setSize(Utils::Vector2D newSize) {
        renderRect.w = newSize.x;
        renderRect.h = newSize.y;
    }

    Utils::Vector2D Texture::getSize() {
        return {static_cast<float>(renderRect.w), static_cast<float>(renderRect.h)};
    }

    void Texture::setPos(Utils::Vector2D newPos) {
        renderRect.x = newPos.x;
        renderRect.y = newPos.y;
    }

    Utils::Vector2D Texture::getPos() {
        return {static_cast<float>(renderRect.x), static_cast<float>(renderRect.y)};
    }

    void Texture::setAngel(float newAngel) {
        angle = Utils::Math::normalizeAngle180(newAngel);
    }

    float Texture::getAngel() {
        return angle;
    }

    void Texture::draw() {
        //renderRect.x = (int)(renderRect.x - renderRect.w*0.5f);
        //renderRect.y = (int)(renderRect.y - renderRect.h*0.5f);

        g_drawing->texture(imgTex, (clipped) ? &clipRect : NULL, &renderRect, angle);
    }


} // Drawing