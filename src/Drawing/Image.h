#ifndef BOSCONIAN_IMAGE_H
#define BOSCONIAN_IMAGE_H

#include "../../includes.h"

namespace Drawing {

    class Image {
    public:
        // some meta data
        const void* mem;
        int dataSize;

        SDL_Texture* img;
        Utils::Vector2D size;
        Utils::Vector2D pos;
        float angle;
        //TODO: may move drawings to Graphics
        SDL_Renderer* renderer;

        Image(SDL_Renderer* renderer, const void* mem, int dataSize, Utils::Vector2D sizeOfImg, float deg = 0.f);
        Image(SDL_Renderer* renderer, const char *file, Utils::Vector2D sizeOfImg, float deg = 0.f);

        void setSize(Utils::Vector2D newSize);
        Utils::Vector2D getSize();

        void setPos(Utils::Vector2D newPos);
        Utils::Vector2D getPos();

        void setAngel(float newAngel);
        float getAngel();

        void draw();
    };

} // Drawing

#endif //BOSCONIAN_IMAGE_H
