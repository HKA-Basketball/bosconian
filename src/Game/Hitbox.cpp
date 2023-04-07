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
        LOG(std::string("Hitbox created from memory"));
    }

    Hitbox::Hitbox(const char *file, Utils::Vector2D sizeOfImg) {
        SDL_Surface* image_surface = IMG_Load(file);
        if (!image_surface)
        {
            LOG(std::string("Error loading image_surface: ") + SDL_GetError());
            return;
        }

        createHitbox(image_surface, sizeOfImg);
        LOG(std::string("Hitbox created from file: ") + file);
    }

    // TODO: WorldToScreen needed!!!
    void Hitbox::updateHitboxPos(Utils::Vector2D pos) {
        if (this->pos == pos)
            return;

        for (int i = 0; i < hitbox_Polygon.size(); i++) {
            hitbox_Polygon[i].x += pos.x - this->pos.x;
            hitbox_Polygon[i].y += pos.y - this->pos.y;
        }
        this->pos = pos;
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
        if (angle == oldAngle)
            return;

        rotatePolygon(hitbox_Polygon, angle, oldAngle, (pos + center));

        oldAngle = angle;
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

    bool isEdgePixel(const std::vector<std::vector<int>>& contour, int x, int y) {
        if (x < 0 || x >= contour[0].size() || y < 0 || y >= contour.size()) {
            return false;
        }
        return contour[y][x] == 1;
    }

    bool isCorner(const std::vector<std::vector<int>>& contour, int x, int y) {
        int numNeighbors = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (isEdgePixel(contour, x + dx, y + dy)) {
                    // Check if the two neighbor pixels are diagonal to each other
                    if (dx != 0 && dy != 0) {
                        continue;
                    }
                    // Check if the two neighbor pixels are on opposite sides of the current pixel
                    if ((dx == -1 && isEdgePixel(contour, x+1, y)) ||
                        (dx == 1 && isEdgePixel(contour, x-1, y)) ||
                        (dy == -1 && isEdgePixel(contour, x, y+1)) ||
                        (dy == 1 && isEdgePixel(contour, x, y-1))) {
                        continue;
                    }

                    numNeighbors++;
                }
            }
        }
        if (numNeighbors != 2) {
            return false;
        }
        return true;
    }

    void Hitbox::createHitbox(SDL_Surface *bmp, Utils::Vector2D displaySize) {
        // TODO: may add Upscaling

        center.x = bmp->w / 2;
        center.y = bmp->h / 2;

        //SDL_Surface* edgeSurface = SDL_CreateRGBSurface(0, bmp->w, bmp->h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

        std::vector<std::vector<int>> contour2D(bmp->h, std::vector<int>(bmp->w, 0));
        for (int y = 0; y < bmp->h; y++) {
            for (int x = 0; x < bmp->w; x++) {
                if (isEdgePixel(bmp, x, y)) {
                    contour2D[y][x] = 1;
                }
            }
        }

        std::vector<std::vector<int>> simplifiedContour = contour2D;
        for (int y = 0; y < bmp->h; y++) {
            for (int x = 0; x < bmp->w; x++) {
                if (contour2D[y][x] == 1 && isCorner(contour2D, x, y)) {
                    simplifiedContour[y][x] = 2;
                }
            }
        }

        /*for (int y = 0; y < bmp->h; y++) {
            for (int x = 0; x < bmp->w; x++) {
                std::cout << simplifiedContour[y][x];
            }
            std::cout << std::endl;
        }*/

        std::vector<SDL_Point> polygon;
        std::vector<std::vector<bool>> visited(bmp->h, std::vector<bool>(bmp->w, false)); // initialize all pixels as unvisited

        // start at any corner pixel and add it to the polygon
        SDL_Point startPixel;
        for (int y = 0; y < bmp->h; y++) {
            for (int x = 0; x < bmp->w; x++) {
                if (simplifiedContour[y][x] == 2) {
                    startPixel = {x, y};
                    break;
                }
            }
        }
        polygon.push_back(startPixel);
        visited[startPixel.y][startPixel.x] = true;

        // create a stack to keep track of pixels to visit
        std::stack<SDL_Point> pixelStack;
        pixelStack.push(startPixel);

        // follow the contour by always moving to the next adjacent corner pixel
        while (!pixelStack.empty()) {
            SDL_Point currentPixel = pixelStack.top();
            pixelStack.pop();
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = currentPixel.x + dx;
                    int ny = currentPixel.y + dy;
                    if (nx >= 0 && nx < bmp->w && ny >= 0 && ny < bmp->h) {
                        if ((simplifiedContour[ny][nx] == 1 || simplifiedContour[ny][nx] == 2) && !visited[ny][nx]) {
                            SDL_Point neighborPixel = {nx, ny};
                            if (simplifiedContour[ny][nx] == 2)
                                polygon.push_back(neighborPixel);

                            visited[ny][nx] = true;
                            pixelStack.push(neighborPixel);
                        }
                    }
                }
            }
        }
        polygon.push_back(startPixel); // close the polygon

        hitbox_Polygon = polygon;

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

    std::vector<SDL_Point> Hitbox::getHitboxPolygon() {
        return this->hitbox_Polygon;
    }
} // Game