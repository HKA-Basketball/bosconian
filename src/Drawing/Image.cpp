#include "../Utilities/Logging.h"
#include "Image.h"

namespace Drawing {
    Image::Image(SDL_Renderer* renderer, const void *mem, int dataSize, Utils::Vector2D sizeOfImg, float deg) {
        this->mem = mem;
        this->dataSize = dataSize;

        this->renderer = renderer;
        size = sizeOfImg;
        angle = deg;

        SDL_RWops* pImgMem = SDL_RWFromConstMem(mem, dataSize);

        if (!pImgMem)
        {
            LOG(std::string("Error loading img Data: ") + SDL_GetError());
            return;
        }

        img = IMG_LoadTexture_RW(renderer, pImgMem, 1);
        if (!img)
        {
            LOG(std::string("Error loading Texture: ") + SDL_GetError());
            return;
        }

        //SDL_QueryTexture(img, NULL, NULL, &w, &h);

        pos = Utils::Vector2D(-1000, -1000);
    }

    Image::Image(SDL_Renderer* renderer, const char *file, Utils::Vector2D sizeOfImg, float deg) {
        this->mem = mem;
        this->dataSize = dataSize;

        this->renderer = renderer;
        size = sizeOfImg;
        angle = deg;

        img = IMG_LoadTexture(renderer, file);
        if (!img)
        {
            LOG(std::string("Error loading Texture: ") + SDL_GetError());
            return;
        }

        pos = Utils::Vector2D(-100, -100);
    }

    void Image::setSize(Utils::Vector2D newSize) {
        size = newSize;
    }

    Utils::Vector2D Image::getSize() {
        return size;
    }

    void Image::setPos(Utils::Vector2D newPos) {
        pos = newPos;
    }

    Utils::Vector2D Image::getPos() {
        return pos;
    }

    void Image::setAngel(float newAngel) {
        // TODO: normalize

        angle = newAngel;
    }

    float Image::getAngel() {
        return angle;
    }

    void Image::draw() {
        // TODO: WorldToScreen & ScreenToWorld ?!

        SDL_Rect rec = { (int)pos.x, (int)pos.y, (int)size.x, (int)size.y };
        SDL_RenderCopyEx(renderer, img, NULL, &rec, angle, NULL, SDL_FLIP_NONE);
    }


} // Drawing