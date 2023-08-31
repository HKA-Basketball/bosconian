#ifndef BOSCONIAN_GAMEMAP_H
#define BOSCONIAN_GAMEMAP_H

class GameMap {
private:
    int width;
    int height;
    // Potentially other properties, e.g. background image, tileset, etc.

public:
    GameMap(int w, int h) : width(w), height(h) {}

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Potentially other functions related to map interactions.
};

#endif //BOSCONIAN_GAMEMAP_H
