#include <stack>
#include "Hitbox.h"

namespace Game {
    Hitbox::Hitbox(const void* mem, int dataSize, Utils::Vector2D sizeOfImg) {
        SDL_RWops* bmpMem = SDL_RWFromConstMem(mem, dataSize);

        if (!bmpMem)
        {
            LOG(std::string("Error loading img Data: ") + SDL_GetError());
            return;
        }

        SDL_Surface* image_surface = IMG_Load_RW(bmpMem, 1);
        if (!image_surface)
        {
            LOG(std::string("Error loading image_surface: ") + SDL_GetError());
            return;
        }

        createHitbox(image_surface, sizeOfImg);
        LOG(std::string("Hitbox created"));
    }

    Hitbox::Hitbox(const char *file, Utils::Vector2D sizeOfImg) {
        SDL_Surface* image_surface = IMG_Load(file);
        if (!image_surface)
        {
            LOG(std::string("Error loading image_surface: ") + SDL_GetError());
            return;
        }

        createHitbox(image_surface, sizeOfImg);
        LOG(std::string("Hitbox created for: ") + file);
    }

    // TODO: WorldToScreen needed!!!
    void Hitbox::updateHitboxPos(Utils::Vector2D pos) {
        this->pos = pos;
        for (int i = 0; i < hitbox_Polygon.size(); i++) {
            hitbox_Polygon[i].x += pos.x;
            hitbox_Polygon[i].y += pos.y;
        }
    }

    // TODO: move to Math Class ?
    void rotatePolygon(std::vector<SDL_Point>& polygon, double angleDegrees, double initialAngle, Utils::Vector2D pivot) {
        // Convert angle to radians
        double angleRadians = (angleDegrees - initialAngle) * M_PI / 180.0;

        // Compute sine and cosine of angle
        double cosAngle = cos(angleRadians);
        double sinAngle = sin(angleRadians);

        // Rotate each point around pivot
        for (SDL_Point& point : polygon) {
            double x = point.x;
            double y = point.y;

            // Apply rotation matrix to point
            double rotatedX = pivot.x + (x - pivot.x) * cosAngle - (y - pivot.y) * sinAngle;
            double rotatedY = pivot.y + (x - pivot.x) * sinAngle + (y - pivot.y) * cosAngle;

            point.x = (int)round(rotatedX);
            point.y = (int)round(rotatedY);
        }
    }

    void Hitbox::updateHitboxAngle(float angle) {
        static unsigned long long oldTCount = SDL_GetTicks64();
        int inputDelay = 250;

        if (SDL_GetTicks64() - oldTCount < inputDelay)
            return;

        static float oldAngle = 0.f;
        if (angle == oldAngle)
            return;

        rotatePolygon(hitbox_Polygon, angle, oldAngle, (pos + center));

        oldAngle = angle;
        oldTCount = SDL_GetTicks64();
    }

    // TODO: may move to Image Class
    Uint32 getPixel(SDL_Surface* surface, int x, int y) {
        int bpp = surface->format->BytesPerPixel;
        Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

        switch (bpp) {
            case 1:
                return *p;
            case 2:
                return *(Uint16*)p;
            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    return p[0] << 16 | p[1] << 8 | p[2];
                else
                    return p[0] | p[1] << 8 | p[2] << 16;
            case 4:
                return *(Uint32*)p;
            default:
                return 0;
        }
    }

    bool isEdgePixel(SDL_Surface* surface, int x, int y) {
        Uint32 pixelColor = getPixel(surface, x, y);
        Uint8 r, g, b, a;
        SDL_GetRGBA(pixelColor, surface->format, &r, &g, &b, &a);
        if (a == 0) {
            return false;  // transparent pixel is not an edge pixel
        }
        if (x == 0 || x == surface->w - 1) {
            return true;
        }
        if (y == 0 || y == surface->h - 1) {
            return true;
        }
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= surface->w || ny < 0 || ny >= surface->h) {
                    continue;
                }
                Uint32 neighborColor = getPixel(surface, nx, ny);
                Uint8 nr, ng, nb, na;
                SDL_GetRGBA(neighborColor, surface->format, &nr, &ng, &nb, &na);
                if (a != na) {
                    return true;
                }
            }
        }
        return false;
    }

    void Hitbox::createHitbox(SDL_Surface *bmp, Utils::Vector2D displaySize) {
        // TODO: may add Upscaling

        center.x = bmp->w / 2;
        center.y = bmp->h / 2;

        //SDL_Surface* edgeSurface = SDL_CreateRGBSurface(0, bmp->w, bmp->h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        std::vector<SDL_Point> contour;

        for (int y = 0; y < bmp->h; y++) {
            for (int x = 0; x < bmp->w; x++) {
                if (isEdgePixel(bmp, x, y)) {
                    contour.push_back({x, y});
                }
            }
        }

        //TODO: may add simplify Contour (reduce points by detecting Lines?)
        //TODO: Idea: find a corner and use a paht algo to go along the line and find the next corner that will be connected to the previous one
        /*
                :----------:
                |          |
                |          |
                |          |
        :-------:          |
        |                  |
        :------------------:
         */

        for (int i = 0; i < contour.size(); i++) {
            hitbox_Polygon.push_back(contour[i]);
        }

        /*for (const SDL_Point& point : hitbox_Polygon) {
            std::cout << "x: " << point.x << ", y: " << point.y << std::endl;
        }*/

        //SDL_SaveBMP(edgeSurface, "./sdf.bmp");
    }

    void Hitbox::printHitbox() {
        for (const auto& rect : hitbox) {
            std::cout << "x: " << rect.x << ", y: " << rect.y << ", w: " << rect.w << ", h: " << rect.h << std::endl;
        }
    }
} // Game