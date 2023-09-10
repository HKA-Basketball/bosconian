#include "Background.h"

Background::Background(SDL_Texture* tex, int mapW, int mapH, int vel)
        : texture(tex), x(0), y(0), velocity(vel), mapWidth(mapW), mapHeight(mapH) {
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Background::~Background() {
    // In this example, we assume that the RenderEngine will take care of destroying the texture.
    // If not, you'd use SDL_DestroyTexture(texture) here.
}

void Background::update(int playerVelocityX, int playerVelocityY) {
    x += playerVelocityX * velocity;
    y += playerVelocityY * velocity;

    // Implement wrapping behavior
    if (x < 0) x += mapWidth;
    if (x > mapWidth) x -= mapWidth;
    if (y < 0) y += mapHeight;
    if (y > mapHeight) y -= mapHeight;
}

void Background::render(RenderEngine& renderEngine, const Camera& camera) {
    // Calculate positions considering wrapping
    /*int xRender = x - camera.getX();
    int yRender = y - camera.getY();

    renderEngine.drawTexture(texture, xRender, yRender);

    // Render wrapped part if necessary
    if (xRender + width < camera.getWidth()) {
        renderEngine.drawTexture(texture, xRender + mapWidth, yRender);
    }
    if (yRender + height < camera.getHeight()) {
        renderEngine.drawTexture(texture, xRender, yRender + mapHeight);
    }*/
}

int Background::getX() const {
    return x;
}

int Background::getY() const {
    return y;
}