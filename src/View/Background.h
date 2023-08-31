#ifndef BOSCONIAN_BACKGROUND_H
#define BOSCONIAN_BACKGROUND_H

#include "RenderEngine.h"
#include "SpriteSheet.h"
#include "../Model/Camera.h"
#include <SDL.h>

class Background {
private:
    SDL_Texture* texture;
    int x, y;
    int width, height;
    int velocity;  // Speed at which the background moves
    int mapWidth, mapHeight;

public:
    Background(SDL_Texture* texture, int mapW, int mapH, int vel = 1);
    ~Background();

    void update(int playerVelocityX, int playerVelocityY); // Update the position based on the player's movement
    void render(RenderEngine& renderEngine, const Camera& camera);

    int getX() const;
    int getY() const;
};

#endif //BOSCONIAN_BACKGROUND_H
