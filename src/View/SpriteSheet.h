#ifndef BOSCONIAN_SPRITESHEET_H
#define BOSCONIAN_SPRITESHEET_H

#include <string>
#include <SDL.h>

class SpriteSheet {
private:
    SDL_Texture* spriteSheet;  // The entire spritesheet
    int spriteWidth;           // Width of a single sprite
    int spriteHeight;          // Height of a single sprite

public:
    SpriteSheet(SDL_Renderer* renderer, const std::string& filepath);
    ~SpriteSheet();

    SDL_Rect GetSprite(int x, int y);  // Returns a rectangle for the sprite at (x,y) position on the sheet
};



#endif //BOSCONIAN_SPRITESHEET_H
