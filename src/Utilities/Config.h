#ifndef BOSCONIAN_CONFIG_H
#define BOSCONIAN_CONFIG_H

#include "SDL.h"

namespace Config {

    const int screenWidth = 896;   // 224 * 4;
    const int screenHeight = 896;  // 224 * 4;
    //  64 * 4
    const int HUDWidth = 256;    //  64 * 4
    const int HUDHeight = 448;    //  64 * 4
    const int HUDVerticalOffset = 320;

    const int livesVerticalOffset = HUDHeight + HUDVerticalOffset;
    const int liveSpriteWidth = (HUDWidth / 5) - 16;
    const int liveSpriteHeight = liveSpriteWidth;

    const int windowWidth = screenWidth + HUDWidth;
    const int windowHeight = screenHeight;

    const int levelWidth = 3000;
    const int levelHeight = 4000;
    const int chunkWidth = 500;
    const int chunkHeight = 500;

    const float parallaxFactor = 0.6f; // Adjust this value to control the strength of the Stars parallax effect

    const float windowCenterX = static_cast<float>(windowWidth)/2;
    const float windowCenterY = static_cast<float>(windowHeight)/2;
    const float screenCenterX = static_cast<float>(screenWidth)/2;
    const float screenCenterY = static_cast<float>(screenHeight)/2;

    const float titlePositionX = windowCenterX;
    const float titlePositionY = 150.f;

    const SDL_Color ColorBlack = {0, 0, 0, 255};
    const SDL_Color ColorWhite = {255, 255, 255, 255};
    const SDL_Color ColorGrey = {128, 128, 128, 255};
    const SDL_Color ColorRed = { 255, 0, 0, 255 };
    const SDL_Color ColorGreen = { 0, 255, 0, 255 };
    const SDL_Color ColorBlue = { 0, 0, 255, 255 };
    const SDL_Color ColorViolet = {150, 0, 222, 255};

}

#endif //BOSCONIAN_CONFIG_H
